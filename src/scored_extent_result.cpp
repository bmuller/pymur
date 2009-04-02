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
