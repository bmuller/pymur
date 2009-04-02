using namespace std;
using namespace indri::api;

class pymur_parsed_document: public Py::PythonExtension<pymur_parsed_document> {
public:
  string content, text;
  Py::Dict metadata;
  Py::List terms;
  static void init_type(void);
  pymur_parsed_document();  
  virtual ~pymur_parsed_document();
  static pymur_parsed_document * fromParsedDocument(ParsedDocument *pd);

  // overwrite PythonExtension methods
  virtual Py::Object repr();
  virtual Py::Object getattr( const char *name );
};
