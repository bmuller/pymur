import tempfile, shutil, sys, unittest, logging
logging.basicConfig(level=logging.DEBUG, format='%(asctime)s %(levelname)s %(message)s')
sys.path.append("src")

logging.debug("Importing pymur...")
import pymur


class PymurTestBase(unittest.TestCase):
    def setUp(self):       
        self.topdir = tempfile.mkdtemp()
        logging.debug("Just made temporary directory at %s" % self.topdir)
        self.index = "%s/%s" % (self.topdir, "index")


    def tearDown(self):
        logging.debug("Deleting toplevel directory at %s" % self.topdir)
        shutil.rmtree(self.topdir)
        
        
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
        

class TestIndexing(PymurTestBase):
    def testStringInput(self):
        txtone = "this is the string one that is a long string"
        txttwo = "this is the string two that has words like the an a"

        ie = self.makeIndexEnvironment()
        ie.addString(txtone, "txt")
        ie.addString(txttwo, "txt")
        ie.close()
        
        qe = self.makeQueryEnvironment()
        docs = qe.documents([1, 2])
        self.assertEqual(docs[0].text, txtone)
        self.assertEqual(docs[1].text, txttwo)
        qe.close()
        

    def testFileInput(self):
        flocation = "./test/data/pubmed.xml"
        
        ie = self.makeIndexEnvironment()
        ie.addFile(flocation, "xml")
        ie.close()

        f = open(flocation, 'r')
        fcontents = f.read()
        f.close()
        
        qe = self.makeQueryEnvironment()
        results = qe.documents([1])
        self.assertEqual(results[0].text, fcontents)
        qe.close()


class TestMetadata(PymurTestBase):
    def testStringMetadata(self):
        ie = self.makeIndexEnvironment(lambda ie: ie.setMetadataIndexedFields(['title'], ['title']))
        ie.addString("this is the string one that is a long string", "txt", {'title': "test one"})
        ie.addString("this is the string two that has words like the an a", "txt", {'title': "test two"})
        ie.close()
    
        qe = self.makeQueryEnvironment()
        docs = qe.documents([1, 2])
        self.assertEqual(docs[0].metadata['title'], "test one")
        self.assertEqual(docs[1].metadata['title'], "test two")
        
        values = qe.documentMetadata([1,2], 'title')
        self.assertEqual(values[0], "test one")
        self.assertEqual(values[1], "test two")

        docs = qe.documentsFromMetadata("title", ["test one", "test two"])
        self.failUnless(len(docs) == 2)


class TestFields(PymurTestBase):
    def testFileFields(self):
        ie = self.makeIndexEnvironment(lambda ie: ie.setIndexedFields(["PMID"], "xml"))
        ie.addFile("./test/data/pubmed.xml", "xml")
        ie.close()

        qe = self.makeQueryEnvironment()
        results = qe.runQuery("11748933.pmid", 3)
        qe.close()

        self.failUnless(len(results) == 1)

        
        
if __name__ == "__main__":
    unittest.main()


