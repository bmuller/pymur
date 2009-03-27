#include "index_environment.h"
 
void pymer_index_environment::init_type() {
  behaviors().name("IndexEnvironment");
  behaviors().doc("indri IndexEnvironment");
  behaviors().supportRepr();
  behaviors().supportGetattr();
  behaviors().supportSequenceType();

  add_varargs_method("create", &pymer_index_environment::create, "create(<index location>)");
}

pymer_index_environment::~pymer_index_environment() {
  index->close();

};

Py::Object pymer_index_environment::create(const Py::Tuple &rargs) {
  if (rargs.length() != 1)
    throw Py::RuntimeError("Incorrect # of args.");

  if (!rargs[0].isString())
    throw Py::TypeError("create takes one string");

  Py::String location(rargs[0]);
  //index.create(location.as_std_string());
  return Py::None();
};

Py::Object pymer_index_environment::repr() {
  return Py::String("an indri IndexEnvironment");
}
