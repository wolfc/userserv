GLIB2_CFLAGS = $(shell pkg-config --cflags glib-2.0)
PIDGIN_LIBDIR = $(shell pkg-config --variable=libdir pidgin)/pidgin

CFLAGS=-fPIC -DPURPLE_PLUGINS -I/usr/include/libpurple -Waggregate-return -Wcast-align -Wdeclaration-after-statement -Wendif-labels -Werror-implicit-function-declaration -Wextra -Wno-sign-compare -Wno-unused-parameter -Wformat -Wformat-security -Winit-self -Wmissing-declarations -Wmissing-noreturn -Wmissing-prototypes -Wpointer-arith -Wundef -Wp,-D_FORTIFY_SOURCE=2 -pthread -O2 $(GLIB2_CFLAGS)

all:	userserv.so

clean:
	rm -f userserv.o userserv.so

userserv.so:	userserv.o
	gcc -shared userserv.o -o $@

install-home:	userserv.so
	mkdir -p ~/.purple/plugins
	cp userserv.so ~/.purple/plugins

install:	$(DESTDIR)/$(PIDGIN_LIBDIR)/userserv.so

$(DESTDIR)/$(PIDGIN_LIBDIR)/userserv.so:userserv.so
	install -D $< $@

rpm:	rpmbuild/SOURCES/pidgin-userserv.tar.gz
	rpmbuild --define "_topdir `pwd`/rpmbuild" -ta $<

rpmbuild/SOURCES/pidgin-userserv.tar.gz:	FORCE
	@mkdir -p rpmbuild/SOURCES
	#git archive --format=tgz --prefix=pidgin-userserv/ HEAD >$@
	tar --transform 's,^,pidgin-userserv/,S' -zcf $@ `git ls-files`

FORCE:
