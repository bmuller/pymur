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

using namespace std;
using namespace indri::api;

class pymur_query_environment: public Py::PythonExtension<pymur_query_environment> {
private:
  QueryEnvironment *env;
public:
  static void init_type(void);
  pymur_query_environment();
  virtual ~pymur_query_environment();
  
  Py::Object addIndex(const Py::Tuple &);
  Py::Object addServer(const Py::Tuple &);
  Py::Object close(const Py::Tuple &);
  Py::Object setScoringRules(const Py::Tuple &);
  Py::Object runQuery(const Py::Tuple &);

  Py::Object setMemory(const Py::Tuple &);
  Py::Object fieldList(const Py::Tuple &);

  Py::Object documents(const Py::Tuple &);
  Py::Object documentCount(const Py::Tuple &);
  Py::Object documentsFromMetadata(const Py::Tuple &);
  Py::Object documentMetadata(const Py::Tuple &);

  // overwrite PythonExtension methods
  virtual Py::Object repr();
};
