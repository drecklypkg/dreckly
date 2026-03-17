$NetBSD$

Fix implicit declaration of exit().

--- bfspeed.c.orig	2026-03-17 07:35:53.636480632 +0000
+++ bfspeed.c
@@ -64,6 +64,7 @@
 #endif
 
 #include <stdio.h>
+#include <stdlib.h>
 #ifndef MSDOS
 #include <unistd.h>
 #else
