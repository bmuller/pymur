import tempfile, shutil, sys, unittest, logging
logging.basicConfig(level=logging.DEBUG, format='%(asctime)s %(levelname)s %(message)s')
sys.path.append("./src")

logging.debug("Importing pymur...")
import pymur

docs = "./docs"
logging.debug("Making HTML documentation in %s directory" % docs)

topdir = tempfile.mkdtemp()
logging.debug("Just made temporary directory at %s" % topdir)
index = "%s/%s" % (topdir, "index")
pymur.IndexEnvironment().create(index)

classes = [(pymur.Index, index),
           (pymur.IndexEnvironment),
           (pymur.QueryEnvironment)
           ]
module = pymur

class IntroDocs:
    def __init__(module, classes, outputdir):
        self.module = module
        self.classes = classes
        self.filename = "%s/index.html" % outputdir


    def makeDocs(self):
        f = open(self.filename, 'w')
        self.writeHeader(f)


        self.writeFooter(f)
        f.close()


    def writeHeader(self, f):
        f.write("<html><head><title>%s Documentation</title></head>" % self.module.__name__)
        f.write("<body><h1>%s Documentation</h1>%s<br /><br />" % (self.module.__name__, self.module.__doc__)) 
    

           
           
