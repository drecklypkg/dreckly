$NetBSD$

Fix implicit declaration of exit().

--- bf_opts.c.orig	2026-03-17 07:36:08.033585536 +0000
+++ bf_opts.c
@@ -64,6 +64,7 @@
 #endif
 
 #include <stdio.h>
+#include <stdlib.h>
 #ifndef MSDOS
 #include <unistd.h>
 #else
