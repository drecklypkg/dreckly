$NetBSD$

Fix implicit declaration of bzero(3).

--- grabhead.c.orig	2026-03-17 07:52:27.303338771 +0000
+++ grabhead.c
@@ -28,6 +28,7 @@
 #include <stdio.h>
 #include <stdlib.h>
 #include <string.h>
+#include <strings.h>
 #include <unistd.h>
 #include <sys/time.h>
 #include <sys/types.h>
