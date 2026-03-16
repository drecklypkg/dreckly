$NetBSD$

Include headers for alloca.

--- src/bk_edit_url_handler.c.orig	2003-11-29 13:14:14.000000000 +0000
+++ src/bk_edit_url_handler.c
@@ -20,6 +20,9 @@
  *
  */
 
+#if defined(__sun) || defined(__linux__)
+#include <alloca.h>
+#endif
 #include <ctype.h>
 #include <string.h>
 #include <stdlib.h>
