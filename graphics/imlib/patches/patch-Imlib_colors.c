$NetBSD$

Include <libgen.h> for basename(3).

--- Imlib/colors.c.orig	2025-12-19 11:21:01.160599240 +0000
+++ Imlib/colors.c
@@ -7,6 +7,8 @@
 #include <string.h>
 #endif
 
+#include <libgen.h>
+
 #ifdef __EMX__
 extern const char *__XOS2RedirRoot(const char*);
 #endif
