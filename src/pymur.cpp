#include "pymur.h"

class pymur_module : public Py::ExtensionModule<pymur_module> {
public:
  pymur_module() : Py::ExtensionModule<pymur_module>("pymur") {
    pymur_index::init_type();
    pymur_index_environment::init_type();

    add_varargs_method("Index", &pymur_module::new_index, "create a new indri Index object");
    add_varargs_method("IndexEnvironment", &pymur_module::new_index_environment, "create a new indri IndexEnvironment object");

    initialize("a python interface to the lemur toolkit");
    Py::Dict d(moduleDictionary());
    d["version"] = Py::String("0.0.1");
    d["author"] = Py::String("bmuller <mullerb@musc.edu>");
  };

  virtual ~pymur_module() {};

  Py::Object new_index(const Py::Tuple &rargs) {
    if (rargs.length() != 1)
      throw Py::RuntimeError("Index takes a single constructor argument of the location of the index");
 
    if (!rargs[0].isString())
      throw Py::TypeError("Index constructor takes one string");

    Py::String location(rargs[0]);
    pymur_index *index = new pymur_index(location.as_std_string());
    if(!index->loaded) {
      throw Py::RuntimeError("Could not load index at " + location.as_std_string());
    }
    return Py::asObject(index);
  };

  Py::Object new_index_environment(const Py::Tuple &rargs) {
    if (rargs.length() != 0)
      throw Py::RuntimeError("IndexEnvironment takes no constructor arguments");
    return Py::asObject(new pymur_index_environment());
  };
};

extern "C" void initpymur() {
  static pymur_module* pymur = new pymur_module();
}
