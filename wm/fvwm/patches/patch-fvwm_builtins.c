$NetBSD$

Include necessary headers for alloca.

--- fvwm/builtins.c.orig	2026-03-16 11:15:18.726384419 +0000
+++ fvwm/builtins.c
@@ -17,7 +17,11 @@
 
 #include "config.h"
 
+#if defined(__sun) || defined(__linux__)
+#include <alloca.h>
+#endif
 #include <stdio.h>
+#include <stdlib.h>
 #include <unistd.h>
 #include <sys/types.h>
 #include <sys/stat.h>
