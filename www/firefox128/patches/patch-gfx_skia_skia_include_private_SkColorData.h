$NetBSD$

Fixes for big endian hardware.
https://bugzilla.mozilla.org/show_bug.cgi?id=1888396

--- gfx/skia/skia/include/private/SkColorData.h.orig	2025-02-24 16:54:51.000000000 +0000
+++ gfx/skia/skia/include/private/SkColorData.h
@@ -12,6 +12,13 @@
 #include "include/core/SkColorPriv.h"
 #include "include/private/base/SkTo.h"
 
+/* Macro to covert between big endian and little endian memory order. */
+#ifdef SK_CPU_BENDIAN
+#define BE_CONVERT(c) ((((c) & 0xff)<<24) | (((c) & 0xff00)<<8) | (((c) & 0xff0000)>>8) | (((c) & 0xff000000)>>24))
+#else
+#define BE_CONVERT(c) c
+#endif
+
 ////////////////////////////////////////////////////////////////////////////////////////////
 // Convert a 16bit pixel to a 32bit pixel
 
