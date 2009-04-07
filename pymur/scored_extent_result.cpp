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

using namespace indri::api;

using namespace std;

void pymur_scored_extent_result::init_type() {
  behaviors().name("ScoredExtentResult");
  behaviors().doc("A ScoredExtent Result");
  behaviors().supportRepr();
  behaviors().supportGetattr();
};


pymur_scored_extent_result::pymur_scored_extent_result() {

};


pymur_scored_extent_result::~pymur_scored_extent_result(){

};


pymur_scored_extent_result * pymur_scored_extent_result::fromScoredExtentResult(ScoredExtentResult &ser) {
  pymur_scored_extent_result *r = new pymur_scored_extent_result();
  r->score = ser.score;
  r->begin = ser.begin;
  r->end = ser.end;
  r->document = ser.document;
  r->number = ser.number;
  return r;
};


Py::Object pymur_scored_extent_result::getattr( const char *name ) {
  if(std::string(name) == "score")
    return Py::Float(score);

  if(std::string(name) == "begin")
    return Py::Int(begin);

  if(std::string(name) == "end")
    return Py::Int(end);

  if(std::string(name) == "document")
    return Py::Int(document);

  if(std::string(name) == "number")
    return Py::Int(number);

  return getattr_methods(name);
}


Py::Object pymur_scored_extent_result::repr() {
  return Py::String("A ScoredExtentResult");
};
