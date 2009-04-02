import pymur
import tempfile, shutil

topdir = tempfile.mkdtemp()
print "created tempdir %s" % topdir

indexdir = "%s/%s" % (topdir, "index")
ie = pymur.IndexEnvironment()
ie.create(indexdir)
ie.addString("string one", "txt", {'title': "test one"})
ie.addString("string two", "txt", {'title': "test two"})
ie.close()

qe = pymur.QueryEnvironment()
qe.addIndex(indexdir)
docs = qe.documents([1, 2])
print docs[0].metadata
print docs[1].metadata

shutil.rmtree(topdir)
