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
        ie = pymur.IndexEnvironment()
        logging.debug("Creating index %s" % self.index)
        ie.create(self.index)
        ie.setStemmer("porter")
        ie.setNormalization(True)
        ie.setStopwords(["one", "two"])
        ie.close()


    def tearDown(self):
        logging.debug("Deleting toplevel directory at %s" % self.topdir)
        #shutil.rmtree(self.topdir)
        
        
    def testStringInput(self):
        return
        ie.setStemmer("porter")
        ie.addString("this is the string one that is a long string", "txt", {'title': "test one"})
        ie.addString("this is the string two that has words like the an a", "txt", {'title': "test two"})
    
        qe = pymur.QueryEnvironment()
        qe.addIndex(self.index)
        docs = qe.documentsFromMetadata("title", ["test one", "test two"])
        print docs
        docs = qe.documents([1, 2])
        print docs[0].content
        print docs[0].text
        print docs[0].terms
        print docs[0].metadata


    def makeQueryEnvironment(self):
        qe = pymur.QueryEnvironment()
        qe.addIndex(self.index)
        return qe


    def makeIndexEnvironment(self):
        ie = pymur.IndexEnvironment()
        ie.open(self.index)
        return ie

    def testFileInput(self):
        ie = self.makeIndexEnvironment()
        ie.setIndexedFields(["PMID"], "xml")
        ie.addFile("./test/pubmed.xml", "xml")
        ie.close()

        qe = self.makeQueryEnvironment()
        results = qe.runQuery("11748933.pmid", 3)
        print results
        qe.close()
        
        
if __name__ == "__main__":
    unittest.main()


