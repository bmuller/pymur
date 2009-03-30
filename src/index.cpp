#include "CXX/Objects.hxx"

#include "index.h"


using namespace std;

// example http://lemur.wiki.sourceforge.net/Example+Applications+in+CPlusPlus
 
void pymer_index::init_type() {
  behaviors().name("Index");
  behaviors().doc("indri Index");
  behaviors().supportRepr();
  //behaviors().supportGetattr();
  behaviors().supportSequenceType();

  add_varargs_method("docCount", &pymer_index::docCount, "docCount() <- Number of documents in index");
}

pymer_index::pymer_index(string location) {
  index = IndexManager::openIndex(location);
};

pymer_index::~pymer_index() {
  delete index;
};

Py::Object pymer_index::docCount(const Py::Tuple &rargs) {
  if (rargs.length() != 0)
    throw Py::RuntimeError("docCount does not take any arguments.");

  Py::Int result = index->docCount();
  return result;
};

Py::Object pymer_index::repr() {
  return Py::String("an indri Index");
}
