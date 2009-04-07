SUBDIRS = src
ACLOCAL_AMFLAGS = -I acinclude.d

test: all
	${PYTHON} test/test.py

docs: all
	${PYTHON} docs/makedocs.py
	@echo 
	@echo "You can view documentation by opening docs/index.html in a browser"
	@echo