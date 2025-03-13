$NetBSD$

Fixes for big endian hardware.
https://bugzilla.mozilla.org/show_bug.cgi?id=1888396

--- gfx/skia/skia/src/core/SkBlitter_ARGB32.cpp.orig	2025-02-24 16:54:51.000000000 +0000
+++ gfx/skia/skia/src/core/SkBlitter_ARGB32.cpp
@@ -1487,7 +1487,7 @@ void SkARGB32_Blitter::blitAntiH(int x, 
         unsigned aa = antialias[0];
         if (aa) {
             if ((opaqueMask & aa) == 255) {
-                SkOpts::memset32(device, color, count);
+                SkOpts::memset32(device, BE_CONVERT(color), count);
             } else {
                 uint32_t sc = SkAlphaMulQ(color, SkAlpha255To256(aa));
                 SkBlitRow::Color32(device, count, sc);
@@ -1503,17 +1503,17 @@ void SkARGB32_Blitter::blitAntiH2(int x,
     uint32_t* device = fDevice.writable_addr32(x, y);
     SkDEBUGCODE((void)fDevice.writable_addr32(x + 1, y);)
 
-    device[0] = SkBlendARGB32(fPMColor, device[0], a0);
-    device[1] = SkBlendARGB32(fPMColor, device[1], a1);
+    device[0] = BE_CONVERT(SkBlendARGB32(fPMColor, BE_CONVERT(device[0]), a0));
+    device[1] = BE_CONVERT(SkBlendARGB32(fPMColor, BE_CONVERT(device[1]), a1));
 }
 
 void SkARGB32_Blitter::blitAntiV2(int x, int y, U8CPU a0, U8CPU a1) {
     uint32_t* device = fDevice.writable_addr32(x, y);
     SkDEBUGCODE((void)fDevice.writable_addr32(x, y + 1);)
 
-    device[0] = SkBlendARGB32(fPMColor, device[0], a0);
+    device[0] = BE_CONVERT(SkBlendARGB32(fPMColor, BE_CONVERT(device[0]), a0));
     device = (uint32_t*)((char*)device + fDevice.rowBytes());
-    device[0] = SkBlendARGB32(fPMColor, device[0], a1);
+    device[0] = BE_CONVERT(SkBlendARGB32(fPMColor, BE_CONVERT(device[0]), a1));
 }
 
 //////////////////////////////////////////////////////////////////////////////////////
@@ -1604,17 +1604,17 @@ void SkARGB32_Opaque_Blitter::blitAntiH2
     uint32_t* device = fDevice.writable_addr32(x, y);
     SkDEBUGCODE((void)fDevice.writable_addr32(x + 1, y);)
 
-    device[0] = SkFastFourByteInterp(fPMColor, device[0], a0);
-    device[1] = SkFastFourByteInterp(fPMColor, device[1], a1);
+    device[0] = BE_CONVERT(SkFastFourByteInterp(fPMColor, BE_CONVERT(device[0]), a0));
+    device[1] = BE_CONVERT(SkFastFourByteInterp(fPMColor, BE_CONVERT(device[1]), a1));
 }
 
 void SkARGB32_Opaque_Blitter::blitAntiV2(int x, int y, U8CPU a0, U8CPU a1) {
     uint32_t* device = fDevice.writable_addr32(x, y);
     SkDEBUGCODE((void)fDevice.writable_addr32(x, y + 1);)
 
-    device[0] = SkFastFourByteInterp(fPMColor, device[0], a0);
+    device[0] = BE_CONVERT(SkFastFourByteInterp(fPMColor, BE_CONVERT(device[0]), a0));
     device = (uint32_t*)((char*)device + fDevice.rowBytes());
-    device[0] = SkFastFourByteInterp(fPMColor, device[0], a1);
+    device[0] = BE_CONVERT(SkFastFourByteInterp(fPMColor, BE_CONVERT(device[0]), a1));
 }
 
 ///////////////////////////////////////////////////////////////////////////////
@@ -1634,7 +1634,7 @@ void SkARGB32_Blitter::blitV(int x, int 
     unsigned dst_scale = SkAlpha255To256(255 - SkGetPackedA32(color));
     size_t rowBytes = fDevice.rowBytes();
     while (--height >= 0) {
-        device[0] = color + SkAlphaMulQ(device[0], dst_scale);
+        device[0] = BE_CONVERT(color + SkAlphaMulQ(BE_CONVERT(device[0]), dst_scale));
         device = (uint32_t*)((char*)device + rowBytes);
     }
 }
@@ -1651,7 +1651,7 @@ void SkARGB32_Blitter::blitRect(int x, i
     size_t      rowBytes = fDevice.rowBytes();
 
     if (SkGetPackedA32(fPMColor) == 0xFF) {
-        SkOpts::rect_memset32(device, color, width, rowBytes, height);
+        SkOpts::rect_memset32(device, BE_CONVERT(color), width, rowBytes, height);
     } else {
         while (height --> 0) {
             SkBlitRow::Color32(device, width, color);
@@ -1680,7 +1680,7 @@ void SkARGB32_Black_Blitter::blitAntiH(i
         unsigned aa = antialias[0];
         if (aa) {
             if (aa == 255) {
-                SkOpts::memset32(device, black, count);
+                SkOpts::memset32(device, BE_CONVERT(black), count);
             } else {
                 SkPMColor src = aa << SK_A32_SHIFT;
                 unsigned dst_scale = 256 - aa;
