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

class pymur_module : public Py::ExtensionModule<pymur_module> {
public:
  pymur_module() : Py::ExtensionModule<pymur_module>("pymur") {
    pymur_index::init_type();
    pymur_index_environment::init_type();
    pymur_query_environment::init_type();
    pymur_parsed_document::init_type();
    pymur_scored_extent_result::init_type();

    add_varargs_method("Index", &pymur_module::new_index, 
		       "Index(<location>): class for running standard queries and determining basic index information");
    add_varargs_method("IndexEnvironment", &pymur_module::new_index_environment, "IndexEnvironment(): class for creating indexes");
    add_varargs_method("QueryEnvironment", &pymur_module::new_query_environment, "QueryEnvironment(): class for making queries");
    add_varargs_method("ParsedDocument", &pymur_module::new_parsed_document, 
		       "ParsedDocument(): class that represents a parsed document.  Has content, text, metadata, and terms attributes.");
    add_varargs_method("ScoredExtentResult", &pymur_module::new_scored_extent_result, 
		       "ScoredExtentResult(): query result type.  Has score, begin, end, document, and number attributes.");

    string description = "A python interface to the Lemur Toolkit. See " + string(PACKAGE_URL) + " for more information.";
    initialize(description.c_str());

    vector<string> version_parts = explode(string(PACKAGE_VERSION), ".");
    Py::Tuple version(version_parts.size());
    for(int i=0; i<version_parts.size(); i++) {
      int vpart = atoi(version_parts[i].c_str());
      version[i] = Py::Int(vpart);
    }

    Py::Dict d(moduleDictionary());    
    d["version"] = version;
    d["copyright"] = Py::String("Copyright 2009 Brian Muller <mullerb@musc.edu>");
  };

  virtual ~pymur_module() {};

  Py::Object new_index(const Py::Tuple &rargs) {
    ArgChecker("Index", rargs).param(STRING, "location of the index").check();
    Py::String location(rargs[0]);
    pymur_index *index = new pymur_index(location.as_std_string());
    if(!index->loaded) {
      throw Py::RuntimeError("Could not load index at " + location.as_std_string());
    }
    return Py::asObject(index);
  };

  Py::Object new_scored_extent_result(const Py::Tuple &rargs) {
    ArgChecker("ScoredExtentResult", rargs).check();
    return Py::asObject(new pymur_scored_extent_result());
  };

  Py::Object new_parsed_document(const Py::Tuple &rargs) {
    ArgChecker("ParsedDocument", rargs).check();
    return Py::asObject(new pymur_parsed_document());
  };

  Py::Object new_index_environment(const Py::Tuple &rargs) {
    ArgChecker("IndexEnvironment", rargs).check();
    return Py::asObject(new pymur_index_environment());
  };

  Py::Object new_query_environment(const Py::Tuple &rargs) {
    ArgChecker("QueryEnvironment", rargs).check();
    return Py::asObject(new pymur_query_environment());
  };
};

extern "C" void initpymur() {
  static pymur_module* pymur = new pymur_module();
}
