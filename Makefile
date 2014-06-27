GLIB2_CFLAGS = $(shell pkg-config --cflags glib-2.0)

CFLAGS=-fPIC -DPURPLE_PLUGINS -I/usr/include/libpurple -Waggregate-return -Wcast-align -Wdeclaration-after-statement -Wendif-labels -Werror-implicit-function-declaration -Wextra -Wno-sign-compare -Wno-unused-parameter -Wformat -Wformat-security -Winit-self -Wmissing-declarations -Wmissing-noreturn -Wmissing-prototypes -Wpointer-arith -Wundef -Wp,-D_FORTIFY_SOURCE=2 -pthread -O2 $(GLIB2_CFLAGS)

all:	userserv.so

clean:
	rm -f userserv.o userserv.so

userserv.so:	userserv.o
	gcc -shared userserv.o -o $@

install: userserv.so
	mkdir -p ~/.purple/plugins
	cp userserv.so ~/.purple/plugins
