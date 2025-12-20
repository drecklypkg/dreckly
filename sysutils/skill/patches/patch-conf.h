$NetBSD$

Add missing include for strncmp(3) and friends.

--- conf.h.orig	2025-12-20 13:08:01.949180782 +0000
+++ conf.h
@@ -28,6 +28,7 @@
 #endif
 #include <sys/stat.h>
 #include <sys/signal.h>
+#include <string.h>
 
 /*
  * Set up common typedef's.
