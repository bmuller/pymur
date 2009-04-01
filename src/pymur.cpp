#include "pymur.h"

class pymur_module : public Py::ExtensionModule<pymur_module> {
public:
  pymur_module() : Py::ExtensionModule<pymur_module>("pymur") {
    pymur_index::init_type();
    pymur_index_environment::init_type();
    pymur_query_environment::init_type();

    add_varargs_method("Index", &pymur_module::new_index, "Index(<location>)create a new indri Index object");
    add_varargs_method("IndexEnvironment", &pymur_module::new_index_environment, "create a new indri IndexEnvironment object");
    add_varargs_method("QueryEnvironment", &pymur_module::new_query_environment, "create a new indri QueryEnvironment object");

    initialize("a python interface to the lemur toolkit");
    Py::Dict d(moduleDictionary());
    d["version"] = Py::String("0.0.1");
    d["author"] = Py::String("bmuller <mullerb@musc.edu>");
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
