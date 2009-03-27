#include "Python.h"
#include "CXX/Objects.hxx"
#include "CXX/Extensions.hxx"

#include "index_environment.h"

class pymer_module : public Py::ExtensionModule<pymer_module> {
public:
  pymer_module() : Py::ExtensionModule<pymer_module>("pymer") {
    pymer_index_environment::init_type();
    add_varargs_method("IndexEnvironment", &pymer_module::new_index_environment, "create a new indri IndexEnvironment");

    initialize("a python interface to the lemur toolkit");
    Py::Dict d(moduleDictionary());
    d["version"] = Py::String("0.0.1");
  };

  virtual ~pymer_module() {};

  Py::Object new_index_environment(const Py::Tuple &rargs) {
    return Py::asObject(new pymer_index_environment());
  }
};

extern "C" void initpymer() {
  static pymer_module* pymer = new pymer_module();
}
