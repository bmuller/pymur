#include "Python.h"
#include "CXX/Objects.hxx"
#include "CXX/Extensions.hxx"

#include "index.h"

class pymer_module : public Py::ExtensionModule<pymer_module> {
public:
  pymer_module() : Py::ExtensionModule<pymer_module>("pymer") {
    pymer_index::init_type();
    add_varargs_method("Index", &pymer_module::new_index, "create a new indri Index object");

    initialize("a python interface to the lemur toolkit");
    Py::Dict d(moduleDictionary());
    d["version"] = Py::String("0.0.1");
  };

  virtual ~pymer_module() {};

  Py::Object new_index(const Py::Tuple &rargs) {
    if (rargs.length() != 1)
      throw Py::RuntimeError("Index takes a single constructor argument of the location of the index");
 
    if (!rargs[0].isString())
      throw Py::TypeError("Index constructor takes one string");

    Py::String location(rargs[0]);
    return Py::asObject(new pymer_index(location.as_std_string()));
  }
};

extern "C" void initpymer() {
  static pymer_module* pymer = new pymer_module();
}
