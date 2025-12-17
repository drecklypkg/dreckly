$NetBSD$

Add missing <cstring> header needed for memset.

--- Source/Core/VideoCommon/TextureDecoder_Generic.cpp.orig	2025-12-17 23:12:36.583573291 +0000
+++ Source/Core/VideoCommon/TextureDecoder_Generic.cpp
@@ -4,6 +4,7 @@
 
 #include <algorithm>
 #include <cmath>
+#include <cstring>
 
 #include "Common/CommonFuncs.h"
 #include "Common/CommonTypes.h"
