#include "CXX/Extensions.hxx"
#include "Index.hpp"
#include "IndexManager.hpp"

using namespace std;
using namespace lemur::api;

class pymer_index: public Py::PythonExtension<pymer_index> {
private:
  Index *index;
public:
  static void init_type(void);
  pymer_index(string location);
  virtual ~pymer_index();
  Py::Object docCount(const Py::Tuple &);

  // overwrite PythonExtension methods
  virtual Py::Object repr();
};
