/*
    Pymur is a Python interface to the Lemur Toolkit.
    Copyright (C) 2009 Brian Muller <mullerb@musc.edu>

    This program is free software: you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation, either version 3 of the License, or
    (at your option) any later version.

    This program is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with this program.  If not, see <http://www.gnu.org/licenses/>.
*/

#include "pymur.h"

using namespace indri::api;
using namespace indri::parse;

using namespace std;

void pymur_index_environment::init_type() {
  behaviors().name("IndexEnvironment");
  behaviors().doc("indri IndexEnvironment");
  behaviors().supportRepr();

  add_varargs_method("setStopwords", &pymur_index_environment::setStopwords, "setStopwords(<list of stopwords>): Manually set stopwords.");
  add_varargs_method("setMemory", &pymur_index_environment::setMemory, "setMemory(<memory size in bytes>)");
  add_varargs_method("setIndexedFields", &pymur_index_environment::setIndexedFields, 
		     "setIndexedFields(<list of fields>, <text class>): Set which fields should be indexed for searches.  "
		     "Text class should be one of txt, xml, html, ...  Note that this method must be called for any fields "
		     "that you intend on searching within.");
  add_varargs_method("setStemmer", &pymur_index_environment::setStemmer, 
		     "setStemmer(<stemmer name>): where stemmer name is porter or krovetz");
  add_varargs_method("setNormalization", &pymur_index_environment::setNormalization, 
		     "setNormalization(<boolean>): set normalization of case and some punctuation; default"
		     " is true (normalize during indexing and at query time) ");
  add_varargs_method("setMetadataIndexedFields", &pymur_index_environment::setMetadataIndexedFields, 
		     "setMetadataIndexedFields(<list of forward field names>, <list of backward field names>): "
		     "Set names of metadata fields to be indexed for fast retrieval. The forward fields are indexed in a "
		     "B-Tree mapping (documentID, metadataValue). If a field is not forward indexed, the documentMetadata "
		     "calls will still work, but they will be slower (the document has to be retrieved, decompressed and "
		     "parsed to get the metadata back, instead of just a B-Tree lookup). The backward indexed fields store "
		     "a mapping of (metadataValue, documentID). If a field is not backward indexed, the "
		     "documentIDsFromMetadata and documentFromMetadata calls will not work.");
  add_varargs_method("documentsSeen", &pymur_index_environment::documentsSeen, "documentsSeen(): get number of docs seen this session");

  add_varargs_method("addFile", &pymur_index_environment::addFile, "addFile(<filelocation>, [<file class>]): add a file with given class");
  add_varargs_method("addString", &pymur_index_environment::addString, "addString(<string>, <file class>, [<metadata dict>]): "
		     "add a given string as the given class.  Accepts optional metadata dictionary - if given, make sure index "
		     "was created with setMetadataIndexedFields called for the given metadata keys.");

  add_varargs_method("create", &pymur_index_environment::create, "create(<location of new index>): Create new index");
  add_varargs_method("open", &pymur_index_environment::open, "open(<index location>): open index");
  add_varargs_method("close", &pymur_index_environment::close, "close(): close index");
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


Py::Object pymur_index_environment::setMetadataIndexedFields(const Py::Tuple &rargs) {
  ArgChecker("setMetadataIndexedFields", rargs).param(LIST).param(LIST).check();
  
  vector<string> forward;
  Py::List pforward(rargs[0]);
  for(unsigned int i=0; i<pforward.length(); i++) {
    if(!pforward[i].isString())
      throw Py::RuntimeError("setMetadataIndexedFields takes a list of strings for both arguments");
    forward.push_back(Py::String(pforward[i]).as_std_string());
  }

  vector<string> backward;
  Py::List pbackward(rargs[1]);
  for(unsigned int i=0; i<pbackward.length(); i++) {
    if(!pbackward[i].isString())
      throw Py::RuntimeError("setMetadataIndexedFields takes a list of strings for both arguments");
    backward.push_back(Py::String(pbackward[i]).as_std_string());
  }
  env.setMetadataIndexedFields(forward, backward);
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
    string field = Py::String(s[i]).as_std_string();
    str_to_lower(field);
    fields.push_back(field);
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
      make_metadata_pair(metadata, key.as_std_string(), value.as_std_string());
      vmetadata.push_back(metadata);
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
