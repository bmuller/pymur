---
layout: base
title: Pymur - Python interface to Lemur
---
# Examples
There are some simple examples listed here.  You can see the test directory for more examples.

## Create Index 
{% highlight python %}
#!python
from pymur import *
i = IndexEnvironment()

# use 1000 bytes
i.setMemory(1000)

# do normalize
i.setNormalization(True)

# set stemmer
i.setStemmer("porter")

# make sure that the metadata we just added is indexed and searchable
# we will make sure "title" is indexed for both forward and backward searches
i.setMetadataIndexedFields(["title"], ["title"])

# make index
i.create("/path/to/index")

# add file
i.addFile("/some/file.xml", "xml")

# add string with metadata
i.addString("this is a string", "txt", {'title': "A String"})

# close index
i.close()
{% endhighlight %}

## Query Index 
{% highlight python %}
#!python
from pymur import *
q = QueryEnvironment()

# get second parsed document and print out the metadata
doc = q.documents([2])[0]
print doc.metadata

# to get the second document's title metadata
print q.documentMetadata([2], 'title')

# get all documents with a metadata field "title" equal to
# the value "A String"
docs = q.documentsFromMetadata("title", ["A String"])

# run an Indri search
docs = q.runQuery("1#(this is)", 2)
{% endhighlight %}

## Index Information 
{% highlight python %}
#!python
from pymur import *
i = Index("/path/to/index")

# get number of documents
print len(i)

# get term at index 3
print i.term(3)

# get number of terms
print i.termCount()

# get document 1 as list of term indexes
doc = i.document(1)

# get document 1 as list of term strings
doc = i.document(1, True)
{% endhighlight %}
