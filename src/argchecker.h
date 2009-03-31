
enum ParamType { NUMBER, STRING, LIST, BOOL };

class ArgChecker {
 private:
  string fname;
  vector<ParamType> params;
  vector<ParamType> oparams;
  Py::Tuple rargs;
  void strFuncDef(string &s);
  static void paramTypeToString(ParamType t, string &s);
  static bool right_type(Py::seqref<Py::Object> obj, ParamType t);
  bool checked;
 public:
  ArgChecker(string _fname, const Py::Tuple &_rargs);
  ~ArgChecker();
  ArgChecker & param(ParamType t);
  ArgChecker & oparam(ParamType t);
  void check();
};
