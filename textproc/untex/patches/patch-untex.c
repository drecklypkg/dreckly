$NetBSD$

Fix implicit declaration of exit(3), strncmp(3).

--- untex.c.orig	2026-06-20 00:54:40.216620001 +0000
+++ untex.c
@@ -44,7 +44,9 @@
 
 
 #include <stddef.h>
+#include <stdlib.h>
 #include <stdio.h>
+#include <string.h>
 #include <ctype.h>
 
 
