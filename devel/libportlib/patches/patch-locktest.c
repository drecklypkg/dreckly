$NetBSD$

Avoid implicit function declarations.

--- locktest.c.orig	1997-01-16 23:18:14.000000000 +0000
+++ locktest.c
@@ -20,6 +20,9 @@
  */
 
 #include	<stdio.h>
+#include	<stdlib.h>
+#include	<string.h>
+#include	<unistd.h>
 
 #include	"portlib.h"
 
