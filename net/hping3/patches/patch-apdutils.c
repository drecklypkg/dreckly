$NetBSD$

SunOS requires alloca.h

--- apdutils.c.orig	2026-03-20 10:09:45.721129738 +0000
+++ apdutils.c
@@ -3,4 +3,7 @@
  */
 
+#ifdef __sun
+#include <alloca.h>
+#endif
 #include <stdio.h>
 #include <string.h>
