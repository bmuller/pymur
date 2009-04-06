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


enum ParamType { NUMBER, STRING, LIST, BOOL, DICT };

class ArgChecker {
 private:
  string fname;
  vector<ParamType> params;
  vector<ParamType> oparams;
  vector<string> params_desc;
  vector<string> oparams_desc;
  Py::Tuple rargs;
  void strFuncDef(string &s);
  static void paramTypeToString(ParamType t, string &s);
  static bool right_type(Py::seqref<Py::Object> obj, ParamType t);
  bool checked;
 public:
  ArgChecker(string _fname, const Py::Tuple &_rargs);
  ~ArgChecker();
  ArgChecker & param(ParamType t, string desc="");
  ArgChecker & oparam(ParamType t, string desc="");
  void check();
};
