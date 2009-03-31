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
  add_varargs_method("setIndexedFields", &pymur_index_environment::setIndexedFields, "setIndexedFields(<List of fields>)");
  add_varargs_method("setStemmer", &pymur_index_environment::setStemmer, "setStemmer(<stemmer name>)");
  add_varargs_method("setNormalization", &pymur_index_environment::setNormalization, "setNormalization(<boolean>)");

  add_varargs_method("addFile", &pymur_index_environment::addFile, "addFile(<filename>, [<file class>])");

  add_varargs_method("create", &pymur_index_environment::create, "create(<location of new index>)");
  add_varargs_method("open", &pymur_index_environment::open, "open(<index location>) <- open index");
  add_varargs_method("close", &pymur_index_environment::close, "close() <- close index");
}


pymur_index_environment::pymur_index_environment() {
  env.setOffsetAnnotationIndexHint(OAHintDefault);
};


pymur_index_environment::~pymur_index_environment() {

};


Py::Object pymur_index_environment::setStopwords(const Py::Tuple &rargs) {
  if(rargs.length() != 1)
    throw Py::RuntimeError("setStopwords takes an array of stopwords");
  if(!rargs[0].isList())
    throw Py::RuntimeError("setStopwords takes an array of stopwords");
  
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
  if(rargs.length() != 1)
    throw Py::RuntimeError("setMemory takes a numeric argument");
  if(!rargs[0].isNumeric())
    throw Py::RuntimeError("setMemory takes a numeric argument");
  long mem = Py::Long(rargs[0]);
  env.setMemory(INT64(mem)); 
  return Py::None();
};


Py::Object pymur_index_environment::setIndexedFields(const Py::Tuple &rargs) {
  if(rargs.length() != 2)
    throw Py::RuntimeError("setIndexedFields takes an array of index field names and a class name");
  if(!rargs[0].isList())
    throw Py::RuntimeError("setIndexedFields takes an array of index field names as first arg");
  if(!rargs[1].isString())
    throw Py::RuntimeError("setIndexedFields takes an array of index field names and a class name");
  
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
  if(rargs.length() != 1 || !rargs[0].isString())
    throw Py::RuntimeError("setStemmer accepts a single string stemmer name");
  string stemmer = Py::String(rargs[0]).as_std_string();
  env.setStemmer(stemmer);
  return Py::None();
};


Py::Object pymur_index_environment::setNormalization(const Py::Tuple &rargs) {
  if(rargs.length() != 1) 
    throw Py::RuntimeError("setNormalization accepts a single boolean argument");
  env.setNormalization(rargs[0].isTrue());
  return Py::None();
};


Py::Object pymur_index_environment::addFile(const Py::Tuple &rargs) {
  if(rargs.length() != 1 && rargs.length() != 2)
    throw Py::RuntimeError("addFile accepts a string file location and an optional string classname");
  if(!rargs[0].isString())
    throw Py::RuntimeError("addFile accepts a string file location and an optional string classname");

  if(rargs.length() == 1) {
    env.addFile(Py::String(rargs[0]).as_std_string());
  } else if(!rargs[1].isString()) {
    throw Py::RuntimeError("addFile accepts a string file location and an optional string classname");
  } else {
    env.addFile(Py::String(rargs[0]).as_std_string(), Py::String(rargs[1]).as_std_string());
  }

  return Py::None();
};


Py::Object pymur_index_environment::create(const Py::Tuple &) {
  //env.create("testindex");
  return Py::None();
};


Py::Object pymur_index_environment::close(const Py::Tuple &) {
  env.close();
  return Py::None();
};


Py::Object pymur_index_environment::open(const Py::Tuple &) {
  //env.open(location);
  return Py::None();
};


Py::Object pymur_index_environment::repr() {
  return Py::String("an indri IndexEnvironment");
};
