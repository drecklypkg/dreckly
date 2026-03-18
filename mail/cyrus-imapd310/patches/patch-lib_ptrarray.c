$NetBSD$

Fix implicit declaration of string functions.

--- lib/ptrarray.c.orig	2025-06-27 02:57:49.000000000 +0000
+++ lib/ptrarray.c
@@ -45,6 +45,7 @@
 
 #include "ptrarray.h"
 #include <memory.h>
+#include <string.h>
 #include "util.h"
 #include "xmalloc.h"
 
