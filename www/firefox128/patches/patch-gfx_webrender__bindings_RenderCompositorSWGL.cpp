$NetBSD$

Fixes for big endian hardware.
https://bugzilla.mozilla.org/show_bug.cgi?id=1888396

--- gfx/webrender_bindings/RenderCompositorSWGL.cpp.orig	2025-02-24 16:54:51.000000000 +0000
+++ gfx/webrender_bindings/RenderCompositorSWGL.cpp
@@ -7,6 +7,7 @@
 #include "RenderCompositorSWGL.h"
 
 #include "mozilla/gfx/Logging.h"
+#include "mozilla/gfx/Swizzle.h"
 #include "mozilla/widget/CompositorWidget.h"
 
 #ifdef MOZ_WIDGET_GTK
@@ -242,6 +243,17 @@ void RenderCompositorSWGL::CommitMappedB
   }
   mDT->Flush();
 
+#if MOZ_BIG_ENDIAN()
+  // One swizzle to rule them all.
+  // With exception to certain text boxes with 1 line (46 pixels) and 2 lines
+  // (64 pixels) in Firefox 115. Per following bug:
+  // https://bugzilla.mozilla.org/show_bug.cgi?id=1900574
+  if ((int)mDT->GetSize().height != 46 && mDT->GetSize().height != 64)
+    gfx::SwizzleData(mMappedData, mMappedStride, gfx::SurfaceFormat::B8G8R8A8,
+                     mMappedData, mMappedStride, gfx::SurfaceFormat::A8R8G8B8,
+                     mDT->GetSize());
+#endif
+
   // Done with the DT. Hand it back to the widget and clear out any trace of it.
   mWidget->EndRemoteDrawingInRegion(mDT, mDirtyRegion);
   mDirtyRegion.SetEmpty();
