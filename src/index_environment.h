using namespace std;
using namespace indri::api;
using namespace indri::parse;

class pymur_index_environment: public Py::PythonExtension<pymur_index_environment> {
private:
  IndexEnvironment env;
public:
  static void init_type(void);
  pymur_index_environment();
  virtual ~pymur_index_environment();

  Py::Object setStopwords(const Py::Tuple &);
  Py::Object setMemory(const Py::Tuple &);
  Py::Object setIndexedFields(const Py::Tuple &);
  Py::Object setStemmer(const Py::Tuple &);
  Py::Object setNormalization(const Py::Tuple &);

  Py::Object addFile(const Py::Tuple &);
  Py::Object addString(const Py::Tuple &);

  Py::Object create(const Py::Tuple &);
  Py::Object close(const Py::Tuple &);
  Py::Object open(const Py::Tuple &);
  Py::Object documentsSeen(const Py::Tuple &);

  // overwrite PythonExtension methods
  virtual Py::Object repr();
};
