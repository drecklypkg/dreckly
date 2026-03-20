$NetBSD$

Need to include <string.h> unconditionally since this uses strcpy(3)
and memset(3).

--- compat.c.orig	2026-03-21 09:05:51.854904736 +0000
+++ compat.c
@@ -11,9 +11,9 @@
 #endif
 
 #include "compat.h"
+#include <string.h>
 
 #ifndef HAVE_STRLCPY
-#include <string.h>
 #include <stdio.h>
 
 void strlcpy(char *dst, const char *src, size_t size)
