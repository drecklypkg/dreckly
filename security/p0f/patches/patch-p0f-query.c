$NetBSD$

Fix implicit declaration of bzero.

--- p0f-query.c.orig	2026-03-17 07:18:24.008587188 +0000
+++ p0f-query.c
@@ -21,6 +21,7 @@
 #include <sys/socket.h>
 #endif
 #include <string.h>
+#include <strings.h>
 
 #include <time.h>
 #include <sys/types.h>
