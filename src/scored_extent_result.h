using namespace std;
using namespace indri::api;

class pymur_scored_extent_result: public Py::PythonExtension<pymur_scored_extent_result> {
public:
  int begin, end, document, number;
  double score;
  static void init_type(void);
  pymur_scored_extent_result();
  virtual ~pymur_scored_extent_result();

  static pymur_scored_extent_result * fromScoredExtentResult(ScoredExtentResult &ser);
  // overwrite PythonExtension methods
  virtual Py::Object repr();
  virtual Py::Object getattr( const char *name );
};
