import shutil, logging
logging.basicConfig(level=logging.DEBUG, format='%(asctime)s %(levelname)s %(message)s')

class IntroDocs:
    def __init__(self, module, classes, outputdir):
        self.module = module
        self.classes = classes
        self.filename = "%s/index.html" % outputdir
        self.classnames = [x[0].__name__ for x in self.classes]


    def makeDocs(self):
        logging.debug("Opening %s for doc creation" % self.filename)
        f = open(self.filename, 'w')
        self.writeHeader(f)
        for klass in self.classes:
            self.handleClass(klass, f)
        self.writeFooter(f)
        f.close()
        logging.debug("Closed %s; documentation process complete" % self.filename)


    def writeHeader(self, f):
        modname = self.module.__name__
        version = ""
        if hasattr(self.module, 'version'):
            version = ".".join(map(lambda x: str(x), self.module.version))
        f.write("<html><head><title>%s %s Documentation</title></head>" % (modname, version))
        docs = self.linkify(self.module.__doc__)
        f.write("<body><h1>%s %s Documentation</h1>%s: %s<br /><br />" % (modname, version, modname, docs)) 
    

    def writeFooter(self, f):
        f.write("</body></html>")
           

    def linkify(self, txt):
        txt = txt.replace("&", "&amp;")
        txt = txt.replace("<", "&lt;")
        txt = txt.replace(">", "&gt;")
        tokens = txt.split(" ")
        for index in range(len(tokens)):
            for classname in self.classnames:
                if tokens[index] == classname:
                    tokens[index] = "<a href=\"#%s\">%s</a>" % (classname, classname)
                elif tokens[index].startswith("http"):
                    tokens[index] = "<a href=\"%s\">%s</a>" % (tokens[index], tokens[index])
        return " ".join(tokens)
        

    def handleClass(self, klassinfo, f):
        klass = klassinfo[0]
        klassname = klass.__name__
        logging.debug("handling class %s" % klassname)
        f.write("<h2><a name=\"%s\" id=\"%s\">%s</a></h2>" % (klassname, klassname, klassname))
        args = klassinfo[1:]
        instance = klass(*args)
        f.write("<ul>")
        f.write("<li>%s</li>" % self.linkify(klass.__doc__))
        for method in dir(instance):
            logging.debug("handling method %s.%s" % (klassname, method))
            docs = getattr(instance, method).__doc__
            f.write("<li>%s</li>" % self.linkify(docs))
        f.write("</ul>")
