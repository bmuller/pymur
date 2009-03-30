#include "index.h"

using namespace std;

// example http://lemur.wiki.sourceforge.net/Example+Applications+in+CPlusPlus
 
void pymur_index::init_type() {
  behaviors().name("Index");
  behaviors().doc("indri Index");
  behaviors().supportRepr();
  //behaviors().supportGetattr();
  behaviors().supportSequenceType();

  add_varargs_method("docCount", &pymur_index::docCount, "docCount() <- Number of documents in index");
  add_varargs_method("__len__", &pymur_index::docCount, "__len__() <- Number of documents in index");
}


pymur_index::pymur_index(string location) {
  index = IndexManager::openIndex(location);
};


pymur_index::~pymur_index() {
  delete index;
};


Py::Object pymur_index::docCount(const Py::Tuple &rargs) {
  if (rargs.length() != 0)
    throw Py::RuntimeError("docCount does not take any arguments.");

  Py::Int result = index->docCount();
  return result;
};


Py::Object pymur_index::repr() {
  return Py::String("an indri Index");
};


int pymur_index::sequence_length() {
  return index->docCount();
};
