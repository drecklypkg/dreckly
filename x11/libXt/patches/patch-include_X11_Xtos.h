$NetBSD$

Fix syntax. Unclear how this ever worked.

--- include/X11/Xtos.h.orig	2025-02-26 22:22:57.079552186 +0000
+++ include/X11/Xtos.h
@@ -64,7 +64,7 @@ SOFTWARE.
     defined(__s390x__) || \
     (defined(__hppa__) && defined(__LP64__)) || \
     defined(__amd64__) || defined(amd64) || \
-    defined(__powerpc64__))
+    defined(__powerpc64__)
 #define LONG64
 #endif
 
