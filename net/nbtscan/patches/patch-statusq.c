$NetBSD$

Fix implicit decl of bzero(3).

--- statusq.c.orig	2026-03-20 20:24:39.066855525 +0000
+++ statusq.c
@@ -28,6 +28,7 @@
 #include <stdlib.h>
 #include <sys/time.h>
 #include <string.h>
+#include <strings.h>
 #include <stdio.h>
 #include <stddef.h>
 #include <ctype.h>
