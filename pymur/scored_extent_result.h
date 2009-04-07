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

class pymur_scored_extent_result: public Py::PythonExtension<pymur_scored_extent_result> {
public:
  int begin, end, document, number;
  double score;
  static void init_type(void);
  pymur_scored_extent_result();
  virtual ~pymur_scored_extent_result();

  static pymur_scored_extent_result * fromScoredExtentResult(ScoredExtentResult &ser);
  // overwrite PythonExtension methods
  virtual Py::Object repr();
  virtual Py::Object getattr( const char *name );
};
