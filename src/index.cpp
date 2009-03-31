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
  IndexedRealVector *results;
  if(rargs.length() == 1) {
    if (!rargs[0].isString())
      throw Py::RuntimeError("runQuery takes a string as first argument");
    results = RetMethodManager::runQuery(Py::String(rargs[0]).as_std_string(), index, "okapi");    
  } else if(rargs.length() == 2) {
    if (!rargs[0].isString() || !rargs[1].isString())
      throw Py::RuntimeError("runQuery takes a strings as first and second arguments");
    results = RetMethodManager::runQuery(Py::String(rargs[0]).as_std_string(), index, Py::String(rargs[1]).as_std_string());    
  } else {
    throw Py::RuntimeError("runQuery takes one or two arguments");
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
  if(rargs.length() > 2 || rargs.length() < 1 || !rargs[0].isNumeric()) 
    throw Py::RuntimeError("document(<index>, [<use words>=False]) at least one integer argument");
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
  if (rargs.length() != 0)
    throw Py::RuntimeError("docCount does not take any arguments.");

  Py::Int result = index->docCount();
  return result;
};


Py::Object pymur_index::termCountUnique(const Py::Tuple &rargs) {
  if (rargs.length() != 0)
    throw Py::RuntimeError("termCountUnique does not take any arguments.");

  Py::Int result = index->termCountUnique();
  return result;
};

Py::Object pymur_index::termCount(const Py::Tuple &rargs) {
  Py::Int result;
  if (rargs.length() == 1) {
    int term = Py::Int(rargs[0]);
    result = index->termCount(term);
  } else if(rargs.length() == 0) {
    result = index->termCount();
  } else {
    throw Py::RuntimeError("termCount takes one or no arguments.");
  }
  return result;
};

Py::Object pymur_index::term(const Py::Tuple &rargs) {
  if (rargs.length() != 1)
    throw Py::RuntimeError("term(<termid>) takes one argument.");

  if (!rargs[0].isNumeric())
    throw Py::TypeError("term(<index>) takes one numerical index argument");

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
