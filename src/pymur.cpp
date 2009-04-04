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

    Py::Tuple version(3);
    version[0] = Py::Int(0);
    version[1] = Py::Int(0);
    version[2] = Py::Int(0);

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
