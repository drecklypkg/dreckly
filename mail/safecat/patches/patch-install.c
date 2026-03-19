$NetBSD$

Fix implicit function declarations.

--- install.c.orig	2000-02-29 04:10:12.000000000 +0000
+++ install.c
@@ -4,6 +4,8 @@
 #include "open.h"
 #include "readwrite.h"
 #include "exit.h"
+#include <sys/stat.h>
+#include <unistd.h>
 
 extern void hier();
 
