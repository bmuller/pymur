
enum ParamType { NUMBER, STRING };

class ArgChecker {
 private:
  string fname;
  vector<ParamType> params;
  Py::Tuple rargs;
 public:
  ArgChecker(string _fname, Py::Tuple &_rargs);
  ArgChecker & param(ParamType t);
  void check();
};
