import tempfile, shutil, sys, unittest, logging
logging.basicConfig(level=logging.DEBUG, format='%(asctime)s %(levelname)s %(message)s')
sys.path.append("./src")

logging.debug("Importing pymur...")
import pymur


class TestQueries(unittest.TestCase):
    def setUp(self):       
        self.topdir = tempfile.mkdtemp()
        logging.debug("Just made temporary directory at %s" % self.topdir)
        self.index = "%s/%s" % (self.topdir, "index")


    def tearDown(self):
        logging.debug("Deleting toplevel directory at %s" % self.topdir)
        #shutil.rmtree(self.topdir)
        
        
    def testStringInput(self):
        ie = self.makeIndexEnvironment()
        ie.addString("this is the string one that is a long string", "txt", {'title': "test one"})
        ie.addString("this is the string two that has words like the an a", "txt", {'title': "test two"})
        ie.close()
    
        qe = self.makeQueryEnvironment()
        docs = qe.documentsFromMetadata("title", ["test one", "test two"])
        print docs


    def makeQueryEnvironment(self):
        qe = pymur.QueryEnvironment()
        qe.addIndex(self.index)
        return qe


    def makeIndexEnvironment(self, f=None):
        logging.debug("Creating index %s" % self.index)
        ie = pymur.IndexEnvironment()
        ie.setStemmer("porter")        
        ie.setNormalization(True)
        if not f is None:
            f(ie)
        ie.create(self.index)
        return ie
        

    def testFileInput(self):
        ie = self.makeIndexEnvironment(lambda ie: ie.setIndexedFields(["PMID"], "xml"))
        ie.addFile("./data/pubmed.xml", "xml")
        ie.close()

        qe = self.makeQueryEnvironment()
        results = qe.runQuery("11748933.pmid", 3)
        qe.close()

        self.failUnless(len(results) == 1)

        
        
if __name__ == "__main__":
    unittest.main()


