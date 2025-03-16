$NetBSD$

Missing header for va_list.

--- Settings.c.orig	2025-03-11 12:55:48.811336194 +0000
+++ Settings.c
@@ -14,6 +14,7 @@ in the source distribution for its full 
 #include <fcntl.h>
 #include <limits.h>
 #include <pwd.h>
+#include <stdarg.h>
 #include <stdio.h>
 #include <stdlib.h>
 #include <string.h>
