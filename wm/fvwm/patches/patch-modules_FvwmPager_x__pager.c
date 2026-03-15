$NetBSD$

Include necessary headers for alloca.

--- modules/FvwmPager/x_pager.c.orig	2026-03-16 11:15:59.376835358 +0000
+++ modules/FvwmPager/x_pager.c
@@ -26,7 +26,11 @@
 
 #include "config.h"
 
+#if defined(__sun) || defined(__linux__)
+#include <alloca.h>
+#endif
 #include <stdio.h>
+#include <stdlib.h>
 #include <signal.h>
 
 #include <X11/Xlib.h>
