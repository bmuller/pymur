import tempfile, shutil, sys, unittest, logging
logging.basicConfig(level=logging.DEBUG, format='%(asctime)s %(levelname)s %(message)s')
sys.path.append("pymur")

logging.debug("Importing pymur...")
import pymur


class PymurTestBase(unittest.TestCase):
    def setUp(self):       
        self.topdir = tempfile.mkdtemp()
        logging.debug("Just made temporary directory at %s" % self.topdir)
        self.index = "%s/%s" % (self.topdir, "index")
        self.xmlfile = "./test/data/pubmed.xml"        


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


    def makeIndex(self):
        return pymur.Index(self.index)


class TestIndexInfo(PymurTestBase):
    def testMetrics(self):
        ie = self.makeIndexEnvironment()
        ie.addFile(self.xmlfile, "xml")
        ie.addFile(self.xmlfile, "xml")
        ie.addString("this is some text", "txt")
        ie.close()

        i = self.makeIndex()
        self.failUnless(len(i) == 3)
        self.assertEqual(i.document(3, True), ['thi', 'is', 'some', 'text'])

        # runQuery returns list of tuples - [(docid, score), ...]
        q = i.runQuery("some")
        self.failUnless(len(q) == 1)
        self.failUnless(q[0][0] == 3)

    def testFields(self):
        ie = self.makeIndexEnvironment(lambda ie: ie.setIndexedFields(["PMID"], "xml"))
        ie.addFile(self.xmlfile, "xml")
        ie.close()

        i = self.makeIndex()
        self.failUnless(i.field(1) == "pmid")

        # there are two pmid fields in our xml document
        info = i.fieldInfoList(1, 1)
        self.failUnless(len(info) == 2)
        # field id should be 1
        self.failUnless(info[0].id == 1)

        

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
        ie = self.makeIndexEnvironment()
        ie.addFile(self.xmlfile, "xml")
        ie.close()

        f = open(self.xmlfile, 'r')
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
        ie.addFile(self.xmlfile, "xml")
        ie.close()

        qe = self.makeQueryEnvironment()
        results = qe.runQuery("11748933.pmid", 3)
        qe.close()

        self.failUnless(len(results) == 1)

        
        
if __name__ == "__main__":
    unittest.main()


