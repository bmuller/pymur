using namespace std;
using namespace indri::api;

class pymur_query_environment: public Py::PythonExtension<pymur_query_environment> {
private:
  QueryEnvironment *env;
public:
  static void init_type(void);
  pymur_query_environment();
  virtual ~pymur_query_environment();
  
  Py::Object addIndex(const Py::Tuple &);
  Py::Object close(const Py::Tuple &);
  Py::Object setScoringRules(const Py::Tuple &);
  Py::Object runQuery(const Py::Tuple &);

  Py::Object documents(const Py::Tuple &);
  Py::Object documentsFromMetadata(const Py::Tuple &);

  // overwrite PythonExtension methods
  virtual Py::Object repr();
};
