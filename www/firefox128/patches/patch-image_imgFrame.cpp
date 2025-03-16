$NetBSD$

Fixes for big endian hardware.
https://bugzilla.mozilla.org/show_bug.cgi?id=1888396

--- image/imgFrame.cpp.orig	2025-02-24 16:54:51.000000000 +0000
+++ image/imgFrame.cpp
@@ -382,6 +382,17 @@ nsresult imgFrame::InitWithDrawable(gfxD
     return NS_ERROR_OUT_OF_MEMORY;
   }
 
+#if MOZ_BIG_ENDIAN()
+  if (aBackend == gfx::BackendType::SKIA && canUseDataSurface) {
+      // SKIA is lying about what format it returns on big endian
+      for (int ii=0; ii < mRawSurface->GetSize().Height()*mRawSurface->Stride() / 4; ++ii) {
+        uint32_t *vals = (uint32_t*)(mRawSurface->GetData());
+        uint32_t val = ((vals[ii] << 8) & 0xFF00FF00 ) | ((vals[ii] >> 8) & 0xFF00FF );
+        vals[ii] = (val << 16) | (val >> 16);
+      }
+  }
+#endif
+
   if (!canUseDataSurface) {
     // We used an offscreen surface, which is an "optimized" surface from
     // imgFrame's perspective.
