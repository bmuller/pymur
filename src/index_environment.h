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
using namespace indri::parse;

class pymur_index_environment: public Py::PythonExtension<pymur_index_environment> {
private:
  IndexEnvironment env;
public:
  static void init_type(void);
  pymur_index_environment();
  virtual ~pymur_index_environment();

  Py::Object setStopwords(const Py::Tuple &);
  Py::Object setMemory(const Py::Tuple &);
  Py::Object setIndexedFields(const Py::Tuple &);
  Py::Object setStemmer(const Py::Tuple &);
  Py::Object setNormalization(const Py::Tuple &);
  Py::Object setMetadataIndexedFields(const Py::Tuple &);

  Py::Object addFile(const Py::Tuple &);
  Py::Object addString(const Py::Tuple &);

  Py::Object create(const Py::Tuple &);
  Py::Object close(const Py::Tuple &);
  Py::Object open(const Py::Tuple &);
  Py::Object documentsSeen(const Py::Tuple &);

  // overwrite PythonExtension methods
  virtual Py::Object repr();
};
