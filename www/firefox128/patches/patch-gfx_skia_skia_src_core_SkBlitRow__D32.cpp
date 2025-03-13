$NetBSD$

Fixes for big endian hardware.
https://bugzilla.mozilla.org/show_bug.cgi?id=1888396

--- gfx/skia/skia/src/core/SkBlitRow_D32.cpp.orig	2025-02-24 16:54:51.000000000 +0000
+++ gfx/skia/skia/src/core/SkBlitRow_D32.cpp
@@ -555,7 +555,7 @@ SkBlitRow::Proc32 SkBlitRow::Factory32(u
 void SkBlitRow::Color32(SkPMColor dst[], int count, SkPMColor color) {
     switch (SkGetPackedA32(color)) {
         case   0: /* Nothing to do */                  return;
-        case 255: SkOpts::memset32(dst, color, count); return;
+        case 255: SkOpts::memset32(dst, BE_CONVERT(color), count); return;
     }
-    return SkOpts::blit_row_color32(dst, count, color);
+    return SkOpts::blit_row_color32(dst, count, BE_CONVERT(color));
 }
