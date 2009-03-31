#include "pymur.h"

ArgChecker::ArgChecker(string _fname, Py::Tuple &_rargs) : fname(_fname) : rargs(_rargs) {
  
};

ArgChecker& ArgChecker::param(ParamType t, boolean optional) {
  params.push_back(Param(t, optional));
  return (*this);
};
  
void ArgChecker::check() {
  if(params.length() != 
  for(unsigned int i=0; i<params.size(); i++) {
    
  }
};
