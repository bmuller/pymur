#include "config.h"
#include "Index.hpp"
#include "IndexManager.hpp"
#include "RetMethodManager.hpp"
#include "IndexedReal.hpp"

#include "Python.h"

#include "CXX/Extensions.hxx"
#include "CXX/Objects.hxx"

using namespace std;
using namespace lemur::api;

class pymur_index: public Py::PythonExtension<pymur_index> {
private:
  Index *index;
public:
  bool loaded;
  static void init_type(void);
  pymur_index(string location);
  virtual ~pymur_index();
  Py::Object docCount(const Py::Tuple &);
  Py::Object termCountUnique(const Py::Tuple &);
  Py::Object termCount(const Py::Tuple &);
  Py::Object term(const Py::Tuple &);
  Py::Object runQuery(const Py::Tuple &);
  Py::Object document(const Py::Tuple &);

  // overwrite PythonExtension methods
  virtual Py::Object repr();
  virtual Py::Object sequence_item(int i);
  virtual int sequence_length();
};
