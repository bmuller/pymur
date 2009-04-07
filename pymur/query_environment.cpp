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

using namespace std;

void pymur_query_environment::init_type() {
  behaviors().name("QueryEnvironment");
  behaviors().doc("indri QueryEnvironment");
  behaviors().supportRepr();

  add_varargs_method("addIndex", &pymur_query_environment::addIndex, 
		     "addIndex(<path to index>): must be called to specify index location");
  add_varargs_method("addServer", &pymur_query_environment::addServer, "addServer(<hostname>): Add a remote server at the "
		     "resolvable hostname to search.");
  add_varargs_method("close", &pymur_query_environment::close, "close(): close the environment");
  add_varargs_method("setScoringRules", &pymur_query_environment::setScoringRules, 
		     "setScoringRules(<string list>): see Lemur examples for rule string format");
  add_varargs_method("runQuery", &pymur_query_environment::runQuery, 
		     "runQuery(<query>, <max results>): run an indri query, returns list of ScoredExtentResult objects");

  add_varargs_method("documents", &pymur_query_environment::documents, 
		     "documents(<list of document ids>): returns list of ParsedDocument objects");
  add_varargs_method("documentsFromMetadata", &pymur_query_environment::documentsFromMetadata, 
		     "documentsFromMetadata(<attribute name>, <list of attribute values to match>): returns "
		     " list of ParsedDocument objects");
  add_varargs_method("documentMetadata", &pymur_query_environment::documentMetadata, 
		     "documentMetadata(<list of document ids>, <attribute name>): Fetch the named metadata attribute "
		     "for a list of document ids. Returns a list of string values.");

  add_varargs_method("fieldList", &pymur_query_environment::fieldList, "fieldList(): Get a list of fieldnames as strings.");
  add_varargs_method("setMemory", &pymur_query_environment::setMemory, "setMemory(<memory size in bytes>): set max amount "
		     "of memory to use when making queries.");
};


pymur_query_environment::pymur_query_environment() {
  env = new QueryEnvironment();
};


pymur_query_environment::~pymur_query_environment() {
  delete env;
};


Py::Object pymur_query_environment::addServer(const Py::Tuple &rargs) {
  ArgChecker("addServer", rargs).param(STRING).check();
  string hostname = Py::String(rargs[0]).as_std_string();
  try {
    env->addServer(hostname);
  } catch(lemur::api::Exception &e) {
    throw Py::RuntimeError("Problem connecting to host \"" + hostname + "\": " + e.what());
  }
  return Py::None();
};


Py::Object pymur_query_environment::fieldList(const Py::Tuple &rargs) {
  ArgChecker("fieldList", rargs).check();
  vector<string> fields = env->fieldList();
  Py::List pfields(fields.size());
  for(int i=0; i<fields.size(); i++)
    pfields[i] = Py::String(fields[i]);
  return pfields;
};


Py::Object pymur_query_environment::setMemory(const Py::Tuple &rargs) {
  ArgChecker("setMemory", rargs).param(NUMBER).check();
  long mem = Py::Long(rargs[0]);
  env->setMemory(INT64(mem));
  return Py::None();
};


Py::Object pymur_query_environment::close(const Py::Tuple &rargs) {
  ArgChecker("close", rargs).check();
  try {
    env->close();
  } catch(Exception &e) {
    throw Py::RuntimeError("Could not close index: " + e.what());
  }
  return Py::None();
};


Py::Object pymur_query_environment::documents(const Py::Tuple &rargs) {
  ArgChecker("documents", rargs).param(LIST).check();
  Py::List pdocids(rargs[0]);
  vector<int> docids;
  for (int i=0; i<pdocids.size(); i++) {
    if(!pdocids[i].isNumeric())
      throw Py::RuntimeError("documents takes a list of integer doc ids");
    int docid = Py::Int(pdocids[i]);
    docids.push_back(docid);
  };

  vector<indri::api::ParsedDocument *> docs;
  try {
    docs = env->documents(docids);
  } catch(Exception &e) {
    throw Py::RuntimeError("Error fetching one or more documents: " + e.what());
  }

  Py::List result((int) docs.size());
  for(int i=0; i<docs.size(); i++) 
    result[i] = Py::asObject(pymur_parsed_document::fromParsedDocument(docs[i]));
  
  return result;
};


Py::Object pymur_query_environment::documentMetadata(const Py::Tuple &rargs) {
  ArgChecker("documentMetadata", rargs).param(LIST).param(STRING).check();
  Py::List pdocids(rargs[0]);
  vector<int> docids;
  for (int i=0; i<pdocids.size(); i++) {
    if(!pdocids[i].isNumeric())
      throw Py::RuntimeError("documentMetadata takes a list of integer doc ids");
    int docid = Py::Int(pdocids[i]);
    docids.push_back(docid);
  };

  string name = Py::String(rargs[1]).as_std_string();
  vector<string> values = env->documentMetadata(docids, name);
  Py::List result(values.size());
  for (int i=0; i<values.size(); i++)
    result[i] = Py::String(values[i]);

  return result;
};


Py::Object pymur_query_environment::documentsFromMetadata(const Py::Tuple &rargs) {
  ArgChecker("documentsFromMetadata", rargs).param(STRING).param(LIST).check();
  string name = Py::String(rargs[0]).as_std_string();
  Py::List pvalues(rargs[1]);
  vector<string> values;
  for (int i=0; i<pvalues.length(); i++) {
    if(!pvalues[i].isString())
      throw Py::RuntimeError("documentsFromMetadata takes a list of strings as the second argument");
    values.push_back(Py::String(pvalues[i]).as_std_string());
  };

  vector<indri::api::ParsedDocument *> docs = env->documentsFromMetadata(name, values);

  Py::List result((int) docs.size());
  for(int i=0; i<docs.size(); i++) 
    result[i] = Py::asObject(pymur_parsed_document::fromParsedDocument(docs[i]));
  
  return result;
};


Py::Object pymur_query_environment::setScoringRules(const Py::Tuple &rargs) {
  ArgChecker("setScoringRules", rargs).param(LIST).check();
  vector<string> rules;
  Py::Sequence s = rargs[0];
  for(unsigned int i=0; i<s.length(); i++) {
    if(!s[i].isString())
      throw Py::RuntimeError("setScoringRules takes an array of string rules");
    rules.push_back(Py::String(s[i]).as_std_string());
  }
  env->setScoringRules(rules);
  return Py::None();
};


Py::Object pymur_query_environment::runQuery(const Py::Tuple &rargs) {
  ArgChecker("runQuery", rargs).param(STRING).param(NUMBER).check();
  string query = Py::String(rargs[0]).as_std_string();
  int max = Py::Int(rargs[1]);

  vector<ScoredExtentResult> results;
  try {
    results = env->runQuery(query, max);
  } catch(Exception &e) {
    throw Py::RuntimeError("problem running query: " + e.what());
  }
  
  Py::List result(results.size());
  for(int i=0; i<results.size(); i++) {
    result[i] = Py::asObject(pymur_scored_extent_result::fromScoredExtentResult(results[i]));
  }
  return result;
};


Py::Object pymur_query_environment::addIndex(const Py::Tuple &rargs) {
  ArgChecker("addIndex", rargs).param(STRING).check();
  try {
    env->addIndex(Py::String(rargs[0]).as_std_string());
  } catch(Exception &e) {
    throw Py::RuntimeError("Could not open index: " + e.what());
  }
  return Py::None();
};


Py::Object pymur_query_environment::repr() {
  return Py::String("an indri QueryEnvironment");
};
