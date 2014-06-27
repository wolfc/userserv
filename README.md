Building
========

# yum install gcc libpurple-devel glib2-devel

Enabling
========

Enable the plugin via Tools -> Plugins (Ctrl-U).
Set password in Edit Account "Password:" field.
Then check "enable userserv auth" in Edit Account -> Advanced.

SELinux
=======

chcon -t textrel_shlib_t ~/.purple/plugins/userserv.so

sudo semanage fcontext -a -t textrel_shlib_t ~/.purple/plugins/userserv.so
