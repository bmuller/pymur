#include "config.h"
#include "Python.h"
#include "CXX/Objects.hxx"
#include "CXX/Extensions.hxx"

#include "index.h"

class pymur_module : public Py::ExtensionModule<pymur_module> {
public:
  pymur_module() : Py::ExtensionModule<pymur_module>("pymur") {
    pymur_index::init_type();
    add_varargs_method("Index", &pymur_module::new_index, "create a new indri Index object");

    initialize("a python interface to the lemur toolkit");
    Py::Dict d(moduleDictionary());
    d["version"] = Py::String("0.0.1");
  };

  virtual ~pymur_module() {};

  Py::Object new_index(const Py::Tuple &rargs) {
    if (rargs.length() != 1)
      throw Py::RuntimeError("Index takes a single constructor argument of the location of the index");
 
    if (!rargs[0].isString())
      throw Py::TypeError("Index constructor takes one string");

    Py::String location(rargs[0]);
    return Py::asObject(new pymur_index(location.as_std_string()));
  }
};

extern "C" void initpymur() {
  static pymur_module* pymur = new pymur_module();
}
