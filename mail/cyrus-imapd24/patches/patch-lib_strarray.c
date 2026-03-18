$NetBSD$

Fix implicit declaration of string functions.

--- lib/strarray.c.orig	2026-03-18 16:28:23.785526101 +0000
+++ lib/strarray.c
@@ -45,6 +45,7 @@
 
 #include "strarray.h"
 #include <memory.h>
+#include <string.h>
 #include "util.h"   /* for strcmpsafe et al */
 #include "xmalloc.h"
 
