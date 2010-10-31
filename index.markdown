---
layout: base
title: Pymur - Python interface to Lemur
---
# Introduction 
**pymur** is a [Python](http://python.org) interface to [The Lemur Toolkit](http://www.lemurproject.org).  You can take a look at the [Examples](examples.html) page to see how the interface can be used.

If you have any questions or would like to help out, please contact bmuller@butterfat.net.

# Installation
## Prerequisites 
 * [Python](http://python.org) ># 2.4 (as well as the Python header files)
 * [Lemur](http://lemurproject.org)

## Compile 
To get the latest version use git:
{% highlight bash %}
git clone git://github.com/bmuller/pymur.git
{% endhighlight %}
To build and install pymur:
{% highlight bash %}
cd pymur
./configure 
make
sudo make install
{% endhighlight %}
Take a look at the [Examples](examples.html) page for examples.


# Testing and Docs
After compiling, you can test the compilation and make API documentation.  To test:
{% highlight bash %}
make test
{% endhighlight %}
And API docs:
{% highlight bash %}
make docs
{% endhighlight %}

# API 
We've attempted to follow the Lemur/Indri API as much as possible (and as much as it makes sense in Python).  Use "make docs" after configuring to generate the current
API docs.

