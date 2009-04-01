#include "pymur.h"

ArgChecker::ArgChecker(string _fname, const Py::Tuple &_rargs) : fname(_fname), rargs(_rargs), checked(false) {
  
};

ArgChecker::~ArgChecker() {
  if(!checked) {
    string fdef, error;
    strFuncDef(fdef);
    error = "Pymur programmer error: In function " + fdef + " an ArgChecker"
      " was created but check() was never called:";
    throw Py::RuntimeError(error);
  }
};

ArgChecker& ArgChecker::param(ParamType t, string desc) {
  params.push_back(t);
  params_desc.push_back(desc);
  return (*this);
};

ArgChecker& ArgChecker::oparam(ParamType t, string desc) {
  oparams.push_back(t);
  oparams_desc.push_back(desc);
  return (*this);  
};

void ArgChecker::paramTypeToString(ParamType t, string &s) {
  switch(t) {
  case NUMBER:
    s = "<number>";
    break;
  case STRING:
    s = "<string>";
    break;
  case LIST:
    s = "<sequence>";
    break;
  case BOOL:
    s = "<boolean>";
    break;
  }
};

void ArgChecker::strFuncDef(string &s) {
  s = fname + "(";
  string sparam;
  for(unsigned int i=0; i<params.size(); i++) {
    ArgChecker::paramTypeToString(params[i], sparam);
    s += sparam;
    if(i < params.size() - 1)
      s += ", ";
  }
  if(params.size() > 0 && oparams.size() > 0)
    s += ", ";
  if(oparams.size() > 0)
    s += "[";
  for(unsigned int i=0; i<oparams.size(); i++) {
    ArgChecker::paramTypeToString(oparams[i], sparam);
    s += sparam;
    if(i < oparams.size() - 1)
      s += ", ";
  }    
  if(oparams.size() > 0)
    s += "]";
  s += ")";
};

bool ArgChecker::right_type(Py::seqref<Py::Object> obj, ParamType t) {
  bool result;
  switch(t) {
  case NUMBER:
    result = obj.isNumeric();
    break;
  case STRING:
    result = obj.isString();
    break;
  case LIST:
    result = obj.isList();
    break;
  default:
    // This will be the default for BOOL: if it's an object, it can
    // be evaluated
    result = true;
    break;
  }
  return result;
};

void ArgChecker::check() {
  string funcdef, stype, snumber, error;
  strFuncDef(funcdef);
  checked = true;

  if(params.size() != rargs.length()) {
    num_to_string((int) params.size(), snumber);
    throw Py::RuntimeError(funcdef + " takes " + snumber + " required argument(s)");
  }

  for(int i=0; i<params.size(); i++) {
    if(!right_type(rargs[i], params[i])) {
      ArgChecker::paramTypeToString(params[i], stype);
      num_to_string(i+1, snumber);
      error = funcdef + " takes a " + stype + " for argument " + snumber;
      error = (params_desc[i] != "") ? (error+"; this is "+params_desc[i]) : error;
      throw Py::RuntimeError(error);
    }
  }

  for(int i=0; i<oparams.size(); i++) {
    if(!right_type(rargs[i], oparams[i])) {
      ArgChecker::paramTypeToString(oparams[i], stype);
      num_to_string(i+1, snumber);
      error = funcdef + " takes a " + stype + " for argument " + snumber;
      error = (params_desc[i] != "") ? (error+"; this is "+params_desc[i]) : error;
      throw Py::RuntimeError(error);
    }
  }
};
