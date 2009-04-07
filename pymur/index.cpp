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

#include "pymur.h"

using namespace std;

// example http://lemur.wiki.sourceforge.net/Example+Applications+in+CPlusPlus
 
void pymur_index::init_type() {
  behaviors().name("Index");
  behaviors().doc("indri Index");
  behaviors().supportRepr();
  behaviors().supportSequenceType();

  add_varargs_method("docCount", &pymur_index::docCount, "docCount([<term id>]): Number of documents in index, or, "
		     "if a term id is given, get number of documents the term appears in.");
  add_varargs_method("termCount", &pymur_index::termCount, "termCount([<term id>]): Number of terms in index, or, "
		     "if a term id is given, number of times that term occurs.");
  add_varargs_method("termCountUnique", &pymur_index::termCountUnique, "termCountUnique(): Number of terms in index");
  add_varargs_method("term", &pymur_index::term, "term(<index>): get term with index, returns string");
  add_varargs_method("runQuery", &pymur_index::runQuery, 
		     "runQuery(<query>, [<model type>=okapi]): same as lemur::api::RetMethodManager::runQuery with text "
		     "query and given model.  Returns a list of tuples that each contain the document id and score.");
  add_varargs_method("document", &pymur_index::document, 
		     "document(<index>, [<use words>=False]): get document, either as list of strings or list of term indexes");
  add_varargs_method("__len__", &pymur_index::docCount, "__len__(): Number of documents in index");

  add_varargs_method("docLength", &pymur_index::docLength, "docLength(<doc id>): Returns number of terms in document.");
  add_varargs_method("docLengthAvg", &pymur_index::docLength, "docLengthAvg(): Returns average number of terms in document.");

  add_varargs_method("fieldInfoList", &pymur_index::fieldInfoList, "fieldInfoList(<doc id>, [<field id>]): Returns a list "
		     "of FieldInfo objects with information about fields (or a specific field if field id is given) available "
		     "in the given document.");
  add_varargs_method("field", &pymur_index::field, "field(<field id>): Get the string field name for the given field id.");
};


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


Py::Object pymur_index::field(const Py::Tuple &rargs) {
  ArgChecker("field", rargs).param(NUMBER).check();
  int fid = Py::Int(rargs[0]);
  string field = "";
  try {
    field = index->field(fid);
  } catch(lemur::api::Exception &e) {
    throw Py::RuntimeError("Problem fetching field: " + e.what());
  }
  return Py::String(field);
};


Py::Object pymur_index::fieldInfoList(const Py::Tuple &rargs) {
  ArgChecker("fieldInfoList", rargs).param(NUMBER).oparam(NUMBER).check();
  int docid = Py::Int(rargs[0]);
  if(docid > index->docCount() || docid == 0)
    throw Py::IndexError("index either out of bounds or zero (there is no document at index 0)");

  Py::List result;
  try {
    FieldInfoList *fil;
    if(rargs.length() == 2) {
      int fieldid = Py::Int(rargs[1]);
      fil = index->fieldInfoList(docid, fieldid);
    } else {
      fil = index->fieldInfoList(docid);
    }
    fil->startIteration();
    while(fil->hasMore()) {
      FieldInfo *fi = fil->nextEntry();
      result.append(Py::asObject(pymur_field_info::fromFieldInfo(fi)));
    }
    delete fil;
  } catch(lemur::api::Exception &e) {
    throw Py::RuntimeError("Problem fetching field info list: " + e.what());
  }
  return result;
};


Py::Object pymur_index::docLength(const Py::Tuple &rargs) {
  ArgChecker("docLength", rargs).param(NUMBER).check();
  int docid = Py::Int(rargs[0]);
  if(docid > index->docCount() || docid == 0)
    throw Py::IndexError("index either out of bounds or zero (there is no document at index 0)");

  int doclength = (int) index->docLength(docid);
  return Py::Int(doclength);
};


Py::Object pymur_index::docLengthAvg(const Py::Tuple &rargs) {
  ArgChecker("docLengthAvg", rargs).check();  
  return Py::Float(index->docLengthAvg());
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
  ArgChecker("docCount", rargs).oparam(NUMBER).check();

  Py::Int result;
  if (rargs.length() == 1) {
    int term = Py::Int(rargs[0]);
    result = index->docCount(term);
  } else if(rargs.length() == 0) {
    result = index->docCount();
  }

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
