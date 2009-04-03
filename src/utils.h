using namespace std;
using namespace indri::api;
using namespace indri::parse;


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
