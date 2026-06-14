$NetBSD$

Fix implicit declaration of exit(3).

--- src/libdes/speed.c.orig	2026-06-14 15:26:09.922438073 +0000
+++ src/libdes/speed.c
@@ -59,6 +59,7 @@
 #include <io.h>
 #endif
 #include <signal.h>
+#include <stdlib.h>
 #ifndef VMS
 #ifndef _IRIX
 #include <time.h>
