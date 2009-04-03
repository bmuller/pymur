#include "pymur.h"

using namespace indri::api;
using namespace indri::parse;

using namespace std;

void debug(string msg) {
#ifdef DEBUG
  string time_s = "";
  time_t rawtime = time(NULL);
  tm *tm_t = localtime(&rawtime);
  char rv[40];
  if(strftime(rv, sizeof(rv)-1, "%a %b %d %H:%M:%S %Y", tm_t))
    time_s = "[" + string(rv) + "] ";
  cout << time_s << "[" << string(PACKAGE_NAME) << "] " << msg << endl;
  cout.flush();
#endif
};

template <class T> bool in_vector(vector<T> things, T thing) {
  for(unsigned int i=0; i<things.size(); i++)
    if(things[i] == thing)
      return true;
  return false;
};

void str_to_lower(string& str) {
  for(int i=0; i<str.size(); i++ )
    str[i] = tolower(str[i]);
};

void make_metadata_pair( indri::parse::MetadataPair &metadata, string key, string value) {
  char *ckey = new char[key.size()+1];
  char *cvalue = new char[value.size()+1];
  strcpy(ckey, key.c_str());
  strcpy(cvalue, value.c_str());

  metadata.key = ckey;
  metadata.value = cvalue;
  metadata.valueLength = value.size()+1;
};

bool addFieldAndConflations(FileClassEnvironmentFactory::Specification *spec, string &name) {
  bool result = false;
  map<ConflationPattern*, string>::const_iterator iter;
  for (iter = spec->conflations.begin(); iter != spec->conflations.end(); iter++) {
    if(iter->second == name && !in_vector<string>(spec->index, iter->first->tag_name)) {
      spec->index.push_back(iter->first->tag_name);
      result = true;
      debug(string(iter->first->tag_name));
      if(!spec->include.empty() && !in_vector<string>(spec->include, iter->first->tag_name))
	spec->include.push_back(iter->first->tag_name);
    }
  }

  // add the original name
  if(!in_vector<string>(spec->index, name)) {
    spec->index.push_back(name);
    result = true;
    if(!spec->include.empty() && !in_vector<string>(spec->include, name))
      spec->include.push_back(name);
  }
  return result;
};

void num_to_string(int i, string& s) {
  char c_int[100];
  sprintf(c_int, "%i", i);
  s = string(c_int);
};

void num_to_string(double i, string& s) {
  char c_int[100];
  sprintf(c_int, "%f", i);
  s = string(c_int);
};
