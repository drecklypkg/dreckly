$NetBSD$

Include <string.h> for strdup, strcmp.

--- src/libquvi/net_wrap.c.orig	2025-12-20 15:50:12.316206786 +0000
+++ src/libquvi/net_wrap.c
@@ -20,6 +20,7 @@
 #include "config.h"
 
 #include <stdlib.h>
+#include <string.h>
 #include <memory.h>
 #include <assert.h>
 
