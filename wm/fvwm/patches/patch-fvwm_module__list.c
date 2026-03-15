$NetBSD$

Include necessary headers for alloca.

--- fvwm/module_list.c.orig	2026-03-16 11:14:53.032765500 +0000
+++ fvwm/module_list.c
@@ -15,6 +15,10 @@
 
 #include "config.h"
 
+#if defined(__sun) || defined(__linux__)
+#include <alloca.h>
+#endif
+#include <stdlib.h>
 #include <errno.h>
 #ifdef HAVE_FCNTL_H
 #include <fcntl.h>
