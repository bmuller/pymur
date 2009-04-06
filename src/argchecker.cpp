/*
    Pymur is a Python interface to the Lemur Toolkit.
    Copyright (C) 2009 Brian Muller <mullerb@musc.edu>

    This program is free software: you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation, either version 3 of the License, or
    (at your option) any later version.

    This program is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with this program.  If not, see <http://www.gnu.org/licenses/>.
*/

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
  case DICT:
    s = "<dictionary>";
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
  case DICT:
    result = obj.isDict();
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

  if(rargs.length() < params.size()) {
    num_to_string((int) params.size(), snumber);
    throw Py::RuntimeError(funcdef + " takes at least " + snumber + " required argument(s)");
  }

  if(rargs.length() > (params.size() + oparams.size())) {
    num_to_string((int) (params.size() + oparams.size()), snumber);
    throw Py::RuntimeError(funcdef + " does not take more than " + snumber + " argument(s)");    
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

  for(int i=params.size(); i<rargs.length(); i++) {
    if(!right_type(rargs[i], oparams[i-params.size()])) {
      ArgChecker::paramTypeToString(oparams[i-params.size()], stype);
      num_to_string(i+1, snumber);
      error = funcdef + " takes a " + stype + " for argument " + snumber;
      error = (oparams_desc[i-params.size()] != "") ? (error+"; this is "+oparams_desc[i-params.size()]) : error;
      throw Py::RuntimeError(error);
    }    
  }
};
