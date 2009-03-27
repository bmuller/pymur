#include "indri/IndexEnvironment.hpp"
#include "CXX/Extensions.hxx"
 
class pymer_index_environment: public Py::PythonExtension<pymer_index_environment> {
private:
  indri::api::IndexEnvironment *index;
public:
  pymer_index_environment() : index() {};
  virtual ~pymer_index_environment();
  static void init_type(void);
  Py::Object create(const Py::Tuple &);

  // overwrite PythonExtension methods
  virtual Py::Object repr();
};
