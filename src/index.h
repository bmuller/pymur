#include "config.h"
#include "Python.h"
#include "Index.hpp"
#include "IndexManager.hpp"

#include "Python.h"

#include "CXX/Extensions.hxx"
#include "CXX/Objects.hxx"

using namespace std;
using namespace lemur::api;

class pymur_index: public Py::PythonExtension<pymur_index> {
private:
  Index *index;
public:
  static void init_type(void);
  pymur_index(string location);
  virtual ~pymur_index();
  Py::Object docCount(const Py::Tuple &);

  // overwrite PythonExtension methods
  virtual Py::Object repr();
  virtual int sequence_length();
};
