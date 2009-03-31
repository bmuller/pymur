#include "pymur.h"

using namespace indri::api;

using namespace std;

void pymur_query_environment::init_type() {
  behaviors().name("QueryEnvironment");
  behaviors().doc("indri QueryEnvironment");
  behaviors().supportRepr();

  add_varargs_method("addIndex", &pymur_query_environment::addIndex, "addIndex(<path to index>)");
  add_varargs_method("setScoringRules", &pymur_query_environment::setScoringRules, "setScoringRules(<string list>)");
  add_varargs_method("runQuery", &pymur_query_environment::runQuery, "runQuery(<query>, <max results>)");
}


pymur_query_environment::pymur_query_environment() {
  env = new QueryEnvironment();
};


pymur_query_environment::~pymur_query_environment() {
  delete env;
};


Py::Object pymur_query_environment::setScoringRules(const Py::Tuple &rargs) {
  ArgChecker("setScoringRules", rargs).param(LIST).check();
  vector<string> rules;
  Py::Sequence s = rargs[0];
  for(unsigned int i=0; i<s.length(); i++) {
    if(!s[i].isString())
      throw Py::RuntimeError("setScoringRules takes an array of string rules");
    rules.push_back(Py::String(s[i]).as_std_string());
  }
  env->setScoringRules(rules);
  return Py::None();
};


Py::Object pymur_query_environment::runQuery(const Py::Tuple &rargs) {
  return Py::Sequence();
};


Py::Object pymur_query_environment::addIndex(const Py::Tuple &rargs) {
  ArgChecker("addIndex", rargs).param(STRING).check();
  try {
    env->addIndex(Py::String(rargs[0]).as_std_string());
  } catch(Exception &e) {
    throw Py::RuntimeError("Could not open index: " + e.what());
  }
  return Py::None();
};


Py::Object pymur_query_environment::repr() {
  return Py::String("an indri QueryEnvironment");
};
