$NetBSD$

--- include/sub.h.orig	2026-03-21 09:20:30.346319589 +0000
+++ include/sub.h
@@ -21,6 +21,8 @@
 #endif
 #include <sys/socket.h>
 #include <net/if.h>
+#include <string.h>
+#include <strings.h>
 
 #ifdef PACKAGE
 #define NAME PACKAGE
