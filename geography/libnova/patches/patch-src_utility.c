$NetBSD$

Fix implicit declaration of alloca(3).

--- src/utility.c.orig	2025-12-20 12:23:08.178327108 +0000
+++ src/utility.c
@@ -44,6 +44,10 @@
 #include <ctype.h>
 #include <libnova/libnova.h>
 
+#if defined(__linux__) || defined(__sun)
+#include <alloca.h>
+#endif
+
 #ifndef __APPLE__
 #include <malloc.h>
 #endif
