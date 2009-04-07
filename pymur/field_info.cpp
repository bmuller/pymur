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

void pymur_field_info::init_type() {
  behaviors().name("FieldInfo");
  behaviors().doc("A FieldInfo object");
  behaviors().supportRepr();
  behaviors().supportGetattr();
};

pymur_field_info::pymur_field_info() {

};

pymur_field_info::~pymur_field_info() {

};

pymur_field_info * pymur_field_info::fromFieldInfo(FieldInfo *fi) {
  pymur_field_info *nfi = new pymur_field_info();
  nfi->begin = fi->begin;
  nfi->end = fi->end;
  nfi->id = fi->id;
  nfi->ordinal = fi->ordinal;
  nfi->parentOrdinal = fi->parentOrdinal;
  nfi->number = fi->number;
  return nfi;
};


Py::Object pymur_field_info::getattr( const char *name ) {
  if(string(name) == "begin")
    return Py::Int(begin);

  if(string(name) == "end")
    return Py::Int(end);

  if(string(name) == "id")
    return Py::Int(id);

  if(string(name) == "ordinal")
    return Py::Int(ordinal);

  if(string(name) == "parentOrdinal")
    return Py::Int(parentOrdinal);

  if(string(name) == "number")
    return Py::Long(number);

  return getattr_methods(name);
}


Py::Object pymur_field_info::repr() {
  return Py::String("A FieldInfo object");
};
