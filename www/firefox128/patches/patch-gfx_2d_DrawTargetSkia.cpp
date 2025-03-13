$NetBSD$

Fixes for big endian hardware.
https://bugzilla.mozilla.org/show_bug.cgi?id=1504834#c10

--- gfx/2d/DrawTargetSkia.cpp.orig	2025-02-24 16:54:51.000000000 +0000
+++ gfx/2d/DrawTargetSkia.cpp
@@ -155,8 +155,12 @@ static IntRect CalculateSurfaceBounds(co
   return surfaceBounds.Intersect(bounds);
 }
 
+#if __sparc
+static const int kARGBAlphaOffset = 0;
+#else
 static const int kARGBAlphaOffset =
     SurfaceFormat::A8R8G8B8_UINT32 == SurfaceFormat::B8G8R8A8 ? 3 : 0;
+#endif
 
 static bool VerifyRGBXFormat(uint8_t* aData, const IntSize& aSize,
                              const int32_t aStride, SurfaceFormat aFormat) {
@@ -2005,6 +2009,14 @@ void DrawTargetSkia::PushLayerWithBlend(
       SkCanvas::kPreserveLCDText_SaveLayerFlag |
           (aCopyBackground ? SkCanvas::kInitWithPrevious_SaveLayerFlag : 0));
 
+#if MOZ_BIG_ENDIAN
+  // Pushing a layer where an aMask is defined produces wrong output.
+  // We _should_ endian swap the data, but I couldn't find a workable way to do so
+  // Therefore I deactivate those layers in the meantime.
+  // The result is: Tab-titles that are longer than the available space should be faded out.
+  //                The fading doesn't work, so we deactivate the fading-effect here.
+  if (!aMask)
+#endif
   mCanvas->saveLayer(saveRec);
 
   SetPermitSubpixelAA(aOpaque);
