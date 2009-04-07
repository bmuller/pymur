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


/** 
 * Print debug messages if DEBUG is defined.
 * 
 * @param msg Message to print
 */
void debug(string msg);


/** 
 * Determine if thing is in things
 * 
 * @param things The things to search
 * @param thing The thing to look for in things
 * 
 * @return True if thing is in things, false otherwise
 */
template <class T> bool in_vector(vector<T> things, T thing);


/** 
 * Add field conflations and a field to a specification index.
 * 
 * @param spec The specification to modify
 * @param name The name of the field
 * 
 * @return True if fields were actually added
 */
bool addFieldAndConflations(FileClassEnvironmentFactory::Specification *spec, string &name);


/** 
 * Convert an int to a string
 * 
 * @param i The int to convert
 * @param s The string to create
 */
void num_to_string(int i, string& s);


/** 
 * Convert a double to a string
 * 
 * @param i The double value to convert
 * @param s The string to put it in
 */
void num_to_string(double i, string& s);


/** 
 * Make a string lowercase
 * 
 * @param str String to make lowercase.
 */
void str_to_lower(string& str);


/** 
 * Create a new indri::parse::MetadataPair with the given key and value.
 * 
 * @param metadata The metadata to set
 * @param key Given key
 * @param value Given value
 */
void make_metadata_pair( indri::parse::MetadataPair &metadata, string key, string value);


/** 
 * Split a string into parts based on delimiter.
 * 
 * @param s The string to split up
 * @param e The delimiter
 * 
 * @return The resulting parts
 */
vector<string> explode(string s, string e);
