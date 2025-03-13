$NetBSD$

Support GLX-only setups.

Inspired by a similar patch in Oracle Solaris.

--- toolkit/xre/glxtest/glxtest.cpp.orig	2025-03-12 14:55:54.938127289 +0000
+++ toolkit/xre/glxtest/glxtest.cpp
@@ -960,9 +960,7 @@ int childgltest(bool aWayland) {
 #ifdef MOZ_X11
   if (!aWayland) {
     // TODO: --display command line argument is not properly handled
-    if (!x11_egltest()) {
-      glxtest();
-    }
+    glxtest();
   }
 #endif
   // Finally write buffered data to the pipe.
