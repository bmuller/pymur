#include "index.h"

// example http://lemur.wiki.sourceforge.net/Example+Applications+in+CPlusPlus
 
void pymer_index::init_type() {
  behaviors().name("Index");
  behaviors().doc("indri Index");
  behaviors().supportRepr();
  //behaviors().supportGetattr();
  behaviors().supportSequenceType();

  //add_varargs_method("create", &pymer_index_environment::create, "create(<index location>)");
  //add_varargs_method("open", &pymer_index_environment::open, "open(<index location>)");
}

pymer_index::~pymer_index() {
  delete index;
};

Py::Object pymer_index::create(const Py::Tuple &rargs) {
  if (rargs.length() != 1)
    throw Py::RuntimeError("Incorrect # of args.");

  if (!rargs[0].isString())
    throw Py::TypeError("create takes one string");

  Py::String location(rargs[0]);
  index->create(location.as_std_string());
  return Py::None();
};

Py::Object pymer_index_environment::open(const Py::Tuple &rargs) {
  if (rargs.length() != 1)
    throw Py::RuntimeError("Incorrect # of args.");

  if (!rargs[0].isString())
    throw Py::TypeError("open takes one string");

  Py::String location(rargs[0]);
  index->open(location.as_std_string());
  return Py::None();
};

Py::Object pymer_index_environment::repr() {
  return Py::String("an indri IndexEnvironment");
}
