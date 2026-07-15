$NetBSD$

Need to include <cmath> for std::isnan.

--- src/towns/highrespcm/highrespcm.cpp.orig	2026-07-15 23:26:49.212335569 +0000
+++ src/towns/highrespcm/highrespcm.cpp
@@ -1,3 +1,4 @@
+#include <cmath>
 #include <stdint.h>
 #include "highrespcm.h"
 #include "towns.h"
