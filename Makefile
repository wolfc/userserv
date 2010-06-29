CFLAGS=-DPURPLE_PLUGINS -I/usr/include/libpurple -I/usr/include/glib-2.0 -I/usr/lib/glib-2.0/include -Waggregate-return -Wcast-align -Wdeclaration-after-statement -Wendif-labels -Werror-implicit-function-declaration -Wextra -Wno-sign-compare -Wno-unused-parameter -Wformat-security -Winit-self -Wmissing-declarations -Wmissing-noreturn -Wmissing-prototypes -Wpointer-arith -Wundef -Wp,-D_FORTIFY_SOURCE=2 -pthread

userserv.so:	userserv.o
	gcc -shared -module -avoid-version userserv.o -o $@

install: userserv.so
	mkdir -p ~/.purple/plugins
	cp userserv.so ~/.purple/plugins
