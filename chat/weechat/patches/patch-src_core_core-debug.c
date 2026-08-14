$NetBSD$

Need _XOPEN_SOURCE=600 for wcwidth.

--- src/core/core-debug.c.orig	2026-08-14 09:01:12.225036791 +0000
+++ src/core/core-debug.c
@@ -22,7 +22,7 @@
 /* Debug functions */
 
 /* for wcwidth in wchar.h */
-#define _XOPEN_SOURCE
+#define _XOPEN_SOURCE 600
 
 #ifdef HAVE_CONFIG_H
 #include "config.h"
