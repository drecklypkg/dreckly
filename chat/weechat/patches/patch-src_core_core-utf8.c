$NetBSD$

Need _XOPEN_SOURCE=600 for wcwidth.

--- src/core/core-utf8.c.orig	2026-08-14 09:02:06.066523691 +0000
+++ src/core/core-utf8.c
@@ -23,7 +23,7 @@
 /* UTF-8 string functions */
 
 /* for wcwidth in wchar.h */
-#define _XOPEN_SOURCE
+#define _XOPEN_SOURCE 600
 
 #ifdef HAVE_CONFIG_H
 #include "config.h"
