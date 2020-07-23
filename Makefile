package = idsh
#version = 0.0.1
tarname = $(package)
distdir = $(tarname)-$(version)

all clean check install uninstall idsh:
	$(MAKE) -C src $@

dist : $(distdir).tar.gz
distclean :
	-rm -rf $(distdir).tar.gz >/dev/null 2>&1
	-rm -rf $(distdir) >/dev/null 2>&1

distcheck : $(distdir).tar.gz
	tar -xaf $(distdir).tar.gz
	$(MAKE) -C $(distdir) all
	$(MAKE) -C $(distdir) check
	$(MAKE) -C $(distdir) DESTDIR=$${PWD}/_install install
	$(MAKE) -C $(distdir) DESTDIR=$${PWD}/_install uninstall
	@remaining="`find $${PWD}/$(distdir)/_install -type f | wc -l`";\
	if test "$${remaining}" -ne 0; then \
	echo "*** $${remaining} files remaining in stage directory!";\
	exit 1;\
	fi
	rm -rf $(distdir)
	@echo "*** Package $(distdir).tar.gz is ready for distribution"

$(distdir).tar.gz : $(distdir)
	tar -cozf $@ $(distdir)
	rm -rf $(distdir)

$(distdir) : distclean
	mkdir -p $(distdir)/src
	cp Makefile $(distdir)
	cp README.md $(distdir)
	cp LICENSE $(distdir)
	cp src/main.c $(distdir)/src
	cp src/Makefile $(distdir)/src

.PHONY : all clean dist distclean distcheck check install uninstall
