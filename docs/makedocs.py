import tempfile, shutil, sys, logging
from intro_docs import IntroDocs
logging.basicConfig(level=logging.DEBUG, format='%(asctime)s %(levelname)s %(message)s')
sys.path.append("pymur")

logging.debug("Importing pymur...")
import pymur

# output directory
docdir = "./docs"

# make temporary directory
logging.debug("Making HTML documentation in %s directory" % docdir)
topdir = tempfile.mkdtemp()
logging.debug("Just made temporary directory at %s" % topdir)
index = "%s/%s" % (topdir, "index")


# create an index
pymur.IndexEnvironment().create(index)


# make docs
classes = [
    [pymur.Index, index],
    [pymur.IndexEnvironment],
    [pymur.QueryEnvironment],
    [pymur.ScoredExtentResult],
    [pymur.ParsedDocument],
    [pymur.FieldInfo]
]
docs = IntroDocs(pymur, classes, docdir)
docs.makeDocs()


# remove temp directory
shutil.rmtree(topdir)
