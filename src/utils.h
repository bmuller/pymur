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
