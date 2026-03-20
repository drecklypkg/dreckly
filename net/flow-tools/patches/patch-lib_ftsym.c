$NetBSD$

Fix implicit function declarations.

--- lib/ftsym.c.orig	2026-03-20 09:41:12.067715094 +0000
+++ lib/ftsym.c
@@ -35,6 +35,7 @@
 #include <ctype.h>
 #include <stddef.h>
 #include <stdlib.h>
+#include <unistd.h>
 
 #if HAVE_STRINGS_H
  #include <strings.h>
