$NetBSD$

As we force C99 we need to also set _LARGEFILE_SOURCE.

--- file.c.orig	2025-02-22 20:31:47.321451776 +0000
+++ file.c
@@ -2,8 +2,10 @@
 
 /* use 64-bit off_t.
  * these macros must be defined before any included file */
+#undef _LARGEFILE_SOURCE
 #undef _LARGEFILE64_SOURCE
 #undef _FILE_OFFSET_BITS
+#define _LARGEFILE_SOURCE
 #define _LARGEFILE64_SOURCE
 #define _FILE_OFFSET_BITS 64
 
