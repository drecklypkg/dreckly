$NetBSD$

Include missing header for strcpy(3).

--- net/bindu.c.orig	2018-02-23 16:24:55.000000000 +0000
+++ net/bindu.c
@@ -21,6 +21,7 @@
 #include <sys/socket.h>
 #include <sys/un.h>
 #include <unistd.h>
+#include <string.h>
 #include "socket.h"
 
 /** Bind a UNIX domain address (path) to a socket. */
