$NetBSD$

https://bugzilla.mozilla.org/show_bug.cgi?id=1490673

--- gfx/angle/checkout/src/compiler/translator/SymbolTable_ESSL_autogen.cpp.orig	2025-03-07 18:40:46.843328760 +0000
+++ gfx/angle/checkout/src/compiler/translator/SymbolTable_ESSL_autogen.cpp
@@ -11,6 +11,7 @@
 
 #ifdef ANGLE_TRANSLATOR_ESSL_ONLY
 
+#    include <cmath>
 #    include "compiler/translator/SymbolTable.h"
 
 #    include "angle_gl.h"
