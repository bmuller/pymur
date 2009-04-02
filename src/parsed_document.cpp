#include "pymur.h"

using namespace indri::api;

using namespace std;

void pymur_parsed_document::init_type() {
  behaviors().name("ParsedDocument");
  behaviors().doc("A ParsedDocument from indri::api::ParsedDocument");
  behaviors().supportRepr();
  behaviors().supportGetattr();
};

pymur_parsed_document::pymur_parsed_document() {

};


pymur_parsed_document::~pymur_parsed_document() {

};

pymur_parsed_document * pymur_parsed_document::fromParsedDocument(ParsedDocument *pd) {
  pymur_parsed_document *npd = new pymur_parsed_document();
  npd->content = pd->getContent();
  npd->text = string(pd->text);

  for(int i=0; i<pd->metadata.size(); i++) {
    string key(pd->metadata[i].key);
    string value((const char *) pd->metadata[i].value, pd->metadata[i].valueLength);
    npd->metadata[key] = Py::String(value);
  }

  for(int i=0; i<pd->terms.size(); i++) {
    Py::String term(string(pd->terms[i]));
    npd->terms.append(term);
  }

  return npd;
};


Py::Object pymur_parsed_document::getattr( const char *name ) {
  if(string(name) == "content")
    return Py::String(content);

  if(string(name) == "text")
    return Py::String(text);

  if(string(name) == "metadata")
    return metadata;

  if(string(name) == "terms")
    return terms;

  return getattr_methods(name);
}


Py::Object pymur_parsed_document::repr() {
  return Py::String("A Indri ParsedDocument");
};
