Building
========

# yum install gcc libpurple-devel glib2-devel

Enabling
========

Enable the plugin via Tools -> Plugins (Ctrl-U).

SELinux
=======

chcon -t textrel_shlib_t '/home/carlo/.purple/plugins/userserv.so'

sudo semanage fcontext -a -t textrel_shlib_t '/home/carlo/.purple/plugins/userserv.so'
