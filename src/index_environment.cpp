#include "pymur.h"

using namespace indri::api;
using namespace indri::parse;

using namespace std;

void pymur_index_environment::init_type() {
  behaviors().name("IndexEnvironment");
  behaviors().doc("indri IndexEnvironment");
  behaviors().supportRepr();

  add_varargs_method("setStopwords", &pymur_index_environment::setStopwords, "setStopwords(<List of stopwords>)");
  add_varargs_method("setMemory", &pymur_index_environment::setMemory, "setMemory(<memory size in bytes>)");
  add_varargs_method("setIndexedFields", &pymur_index_environment::setIndexedFields, "setIndexedFields(<List of fields>, <text class>)");
  add_varargs_method("setStemmer", &pymur_index_environment::setStemmer, "setStemmer(<stemmer name>)");
  add_varargs_method("setNormalization", &pymur_index_environment::setNormalization, "setNormalization(<boolean>)");
  add_varargs_method("documentsSeen", &pymur_index_environment::documentsSeen, "documentsSeen() <- # docs seen this session");

  add_varargs_method("addFile", &pymur_index_environment::addFile, "addFile(<filename>, [<file class>])");
  add_varargs_method("addString", &pymur_index_environment::addString, "addString(<string>, <file class>, [<metadata dict>])");

  add_varargs_method("create", &pymur_index_environment::create, "create(<location of new index>)");
  add_varargs_method("open", &pymur_index_environment::open, "open(<index location>) <- open index");
  add_varargs_method("close", &pymur_index_environment::close, "close() <- close index");
}


pymur_index_environment::pymur_index_environment() {
  env.setOffsetAnnotationIndexHint(OAHintDefault);
};


pymur_index_environment::~pymur_index_environment() {
  try {
    env.close();
  } catch(Exception &e) {
    throw Py::RuntimeError("Could not close index: " + e.what());
  } 
};


Py::Object pymur_index_environment::documentsSeen(const Py::Tuple &rargs) {
  ArgChecker("documentsSeen", rargs).check();
  return Py::Int(env.documentsSeen());
};


Py::Object pymur_index_environment::setStopwords(const Py::Tuple &rargs) {
  ArgChecker("setStopwords", rargs).param(LIST).check();
  
  vector<string> stopwords;
  Py::Sequence s = rargs[0];
  for(unsigned int i=0; i<s.length(); i++) {
    if(!s[i].isString())
      throw Py::RuntimeError("setStopwords takes an array of stopwords");
    stopwords.push_back(Py::String(s[i]).as_std_string());
  }
  env.setStopwords(stopwords);
  return Py::None();
};


Py::Object pymur_index_environment::setMemory(const Py::Tuple &rargs) {
  ArgChecker("setMemory", rargs).param(NUMBER).check();
  long mem = Py::Long(rargs[0]);
  env.setMemory(INT64(mem)); 
  return Py::None();
};


Py::Object pymur_index_environment::setIndexedFields(const Py::Tuple &rargs) {
  ArgChecker("setIndexedFields", rargs).param(LIST).param(STRING).check();
  vector<string> fields;
  Py::Sequence s = rargs[0];
  for(unsigned int i=0; i<s.length(); i++) {
    if(!s[i].isString())
      throw Py::RuntimeError("setIndexedFields takes an array of index field names as first arg");
    fields.push_back(Py::String(s[i]).as_std_string());
  }

  env.setIndexedFields(fields);

  // Next bit may seem unecessary - but using same format/process as IndriBuildIndex.cpp
  string classname = Py::String(rargs[1]).as_std_string();
  FileClassEnvironmentFactory::Specification *spec = env.getFileClassSpec(classname);
  if(spec) {
    bool changed = false;
    for(unsigned int i=0; i<fields.size(); i++)
      changed = changed || addFieldAndConflations(spec, fields[i]);
    if(changed) {
      debug("file class " + classname + " had fields added and was added to the environment as a new spec");
      env.addFileClass(*spec);
    }
    delete(spec);
  }

  return Py::None();
};


Py::Object pymur_index_environment::setStemmer(const Py::Tuple &rargs) {
  ArgChecker("setStemmer", rargs).param(STRING).check();
  string stemmer = Py::String(rargs[0]).as_std_string();
  env.setStemmer(stemmer);
  return Py::None();
};


Py::Object pymur_index_environment::setNormalization(const Py::Tuple &rargs) {
  ArgChecker("setStemmer", rargs).param(BOOL).check();
  env.setNormalization(rargs[0].isTrue());
  return Py::None();
};


Py::Object pymur_index_environment::addFile(const Py::Tuple &rargs) {
  ArgChecker("addFile", rargs).param(STRING).oparam(STRING).check();
  int docsseen = env.documentsSeen();
  string fname = Py::String(rargs[0]).as_std_string();
  if(rargs.length() == 1) {
    env.addFile(fname);
  } else {
    env.addFile(fname, Py::String(rargs[1]).as_std_string());
  }

  if(env.documentsSeen() == docsseen) 
    throw Py::RuntimeError("Problem reading file \"" + fname + "\"");

  return Py::None();
};


Py::Object pymur_index_environment::addString(const Py::Tuple &rargs) {
  ArgChecker("addString", rargs).param(STRING).param(STRING).oparam(DICT).check();
  string docstring = Py::String(rargs[0]).as_std_string();
  string fclass = Py::String(rargs[1]).as_std_string();
  vector<indri::parse::MetadataPair> vmetadata;

  if(rargs.length() == 3) {
    Py::Dict mdp(rargs[2]);
    for(int i=0; i < mdp.length(); i++) {
      Py::String key(mdp.keys()[i]);
      Py::String value(mdp[key]);
      indri::parse::MetadataPair metadata;
      metadata.key = key.as_std_string().c_str();
      metadata.value = value.as_std_string().c_str();
      metadata.valueLength = value.length();
      vmetadata.push_back(metadata);
      debug("Adding metadata field " + string(metadata.key) + ": " + string((const char *) metadata.value));
    }
  }

  int docid = (int) env.addString(docstring, fclass, vmetadata);
  return Py::Int(docid);
};


Py::Object pymur_index_environment::create(const Py::Tuple &rargs) {
  ArgChecker("create", rargs).param(STRING).check();
  try {
    env.create(Py::String(rargs[0]).as_std_string());
  } catch(Exception &e) {
    throw Py::RuntimeError("Could not create index: " + e.what());
  }
  return Py::None();
};


Py::Object pymur_index_environment::close(const Py::Tuple &rargs) {
  ArgChecker("close", rargs).check();
  try {
    env.close();
  } catch(Exception &e) {
    throw Py::RuntimeError("Could not close index: " + e.what());
  } 
  return Py::None();
};


Py::Object pymur_index_environment::open(const Py::Tuple &rargs) {
  ArgChecker("open", rargs).param(STRING).check();
  try {
    env.open(Py::String(rargs[0]).as_std_string());
  } catch(Exception &e) {
    throw Py::RuntimeError("Could not open index: " + e.what());
  }
  return Py::None();
};


Py::Object pymur_index_environment::repr() {
  return Py::String("an indri IndexEnvironment");
};
