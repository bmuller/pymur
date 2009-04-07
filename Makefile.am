SUBDIRS = pymur
ACLOCAL_AMFLAGS = -I acinclude.d

nobase_include_HEADERS = pymur/argchecker.h pymur/field_info.h pymur/index.h pymur/pymur.h pymur/scored_extent_result.h \
        pymur/config.h pymur/index_environment.h pymur/parsed_document.h pymur/query_environment.h pymur/utils.h \
        pymur/CXX/Config.hxx pymur/CXX/Extensions.hxx pymur/CXX/Objects.hxx pymur/CXX/WrapPython.h pymur/CXX/Exception.hxx \
        pymur/CXX/IndirectPythonInterface.hxx pymur/CXX/Version.hxx

EXTRA_DIST = test/test.py test/data/pubmed.xml docs/intro_docs.py docs/makedocs.py

test: all
	${PYTHON} test/test.py

docs: all
	${PYTHON} docs/makedocs.py
	@echo 
	@echo "You can view documentation by opening docs/index.html in a browser"
	@echo