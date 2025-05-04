$NetBSD$

Fix build on OpenBSD.

--- src/libvncserver/main.c.orig	2025-05-04 08:19:29.686890251 +0000
+++ src/libvncserver/main.c
@@ -17,6 +17,7 @@
 #include <rfb/rfbregion.h>
 #include "private.h"
 
+#include <sys/socket.h>
 #include <stdarg.h>
 #include <errno.h>
 
