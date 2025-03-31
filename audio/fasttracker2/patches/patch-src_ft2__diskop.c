$NetBSD$

Fix build with older glibc which does not like fts.h being included
when _FILE_OFFSET_BITS is defined.

--- src/ft2_diskop.c.orig	2025-03-31 21:27:31.508418094 +0000
+++ src/ft2_diskop.c
@@ -3,7 +3,9 @@
 #include <crtdbg.h>
 #endif
 
+#ifndef __linux
 #define _FILE_OFFSET_BITS 64
+#endif
 
 #include <stdint.h>
 #include <stdio.h>
