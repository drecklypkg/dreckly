$NetBSD$

Fixes for big endian hardware.
https://bugzilla.mozilla.org/show_bug.cgi?id=1344659

--- gfx/2d/Types.h.orig	2025-02-24 16:54:51.000000000 +0000
+++ gfx/2d/Types.h
@@ -92,15 +92,8 @@ enum class SurfaceFormat : int8_t {
 // The following values are endian-independent synonyms. The _UINT32 suffix
 // indicates that the name reflects the layout when viewed as a uint32_t
 // value.
-#if MOZ_LITTLE_ENDIAN()
   A8R8G8B8_UINT32 = B8G8R8A8,  // 0xAARRGGBB
   X8R8G8B8_UINT32 = B8G8R8X8,  // 0x00RRGGBB
-#elif MOZ_BIG_ENDIAN()
-  A8R8G8B8_UINT32 = A8R8G8B8,  // 0xAARRGGBB
-  X8R8G8B8_UINT32 = X8R8G8B8,  // 0x00RRGGBB
-#else
-#  error "bad endianness"
-#endif
 
   // The following values are OS and endian-independent synonyms.
   //
