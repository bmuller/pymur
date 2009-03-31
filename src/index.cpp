#include "pymur.h"

using namespace std;

// example http://lemur.wiki.sourceforge.net/Example+Applications+in+CPlusPlus
 
void pymur_index::init_type() {
  behaviors().name("Index");
  behaviors().doc("indri Index");
  behaviors().supportRepr();
  //behaviors().supportGetattr();
  behaviors().supportSequenceType();

  add_varargs_method("docCount", &pymur_index::docCount, "docCount() <- Number of documents in index");
  add_varargs_method("termCount", &pymur_index::termCount, "termCount() <- Number of terms in index");
  add_varargs_method("termCountUnique", &pymur_index::termCountUnique, "termCountUnique() <- Number of terms in index");
  add_varargs_method("term", &pymur_index::term, "term(<index>) <- get term with index");
  add_varargs_method("runQuery", &pymur_index::runQuery, "runQuery(<query>, [<model type>=okapi]) <- get term with index");
  add_varargs_method("document", &pymur_index::document, "document(<index>, [<use words>=False]) <- get document");
  add_varargs_method("__len__", &pymur_index::docCount, "__len__() <- Number of documents in index");
}


pymur_index::pymur_index(string location) : loaded(false) {
  try {
    index = IndexManager::openIndex(location);
    loaded = true;
  } catch(lemur::api::Exception &e) {
    // loaded will be false
  }
};


pymur_index::~pymur_index() {
  if(loaded)
    delete index;
};


Py::Object pymur_index::runQuery(const Py::Tuple &rargs) {
  ArgChecker("runQuery", rargs).param(STRING).oparam(STRING).check();
  IndexedRealVector *results;
  if(rargs.length() == 1) {
    results = RetMethodManager::runQuery(Py::String(rargs[0]).as_std_string(), index, "okapi");    
  } else {
    results = RetMethodManager::runQuery(Py::String(rargs[0]).as_std_string(), index, Py::String(rargs[1]).as_std_string());    
  }

  Py::List l;
  for (int i=0; i < results->size(); i++) {
    Py::Tuple t(2);
    t[0] = Py::Int((*results)[i].ind);
    t[1] = Py::Float((*results)[i].val);
    l.append(t);
  }
  delete results;
  return l;
};

Py::Object pymur_index::document(const Py::Tuple &rargs) {
  ArgChecker("document", rargs).param(NUMBER).oparam(BOOL).check();
  bool usewords = (rargs.length() == 2 && rargs[1].isTrue());
  int docid = Py::Int(rargs[0]);
  if(docid > index->docCount() || docid == 0)
    throw Py::IndexError("index either out of bounds or zero (there is no document at index 0)");

  Py::List l;
  TermInfoList *termList = index->termInfoListSeq(docid);
  if(termList) {
    termList->startIteration();
    while (termList->hasMore()) {
      TermInfo *thisTerm=termList->nextEntry();
      int thisTermID=thisTerm->termID();
      if(usewords) 
	l.append(Py::String(index->term(thisTermID)));
      else
	l.append(Py::Int(thisTermID));
    } 
    delete termList;
  }
  return l;
};

Py::Object pymur_index::docCount(const Py::Tuple &rargs) {
  ArgChecker("docCount", rargs).check();
  Py::Int result = index->docCount();
  return result;
};


Py::Object pymur_index::termCountUnique(const Py::Tuple &rargs) {
  ArgChecker("termCountUnique", rargs).check();
  Py::Int result = index->termCountUnique();
  return result;
};

Py::Object pymur_index::termCount(const Py::Tuple &rargs) {
  ArgChecker("termCount", rargs).oparam(NUMBER).check();
  Py::Int result;
  if (rargs.length() == 1) {
    int term = Py::Int(rargs[0]);
    result = index->termCount(term);
  } else if(rargs.length() == 0) {
    result = index->termCount();
  }
  return result;
};

Py::Object pymur_index::term(const Py::Tuple &rargs) {
  ArgChecker("term", rargs).param(NUMBER).check();
  Py::Int term(rargs[0]);
  if(term >= index->termCount())
    throw Py::IndexError("term index out of bounds");
  return Py::String(index->term(term));
};


Py::Object pymur_index::repr() {
  return Py::String("an indri Index");
};


int pymur_index::sequence_length() {
  return index->docCount();
};

Py::Object pymur_index::sequence_item(int i) {
  Py::Tuple args(1);
  args[0] = Py::Int(i);
  return document(args);
};
