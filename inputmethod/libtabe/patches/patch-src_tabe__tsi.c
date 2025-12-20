$NetBSD$

Avoid implicit declaration of fabs(3).

--- src/tabe_tsi.c.orig	2025-12-20 12:35:30.938250523 +0000
+++ src/tabe_tsi.c
@@ -14,6 +14,7 @@
 #include <stdio.h>
 #include <stdlib.h>
 #include <string.h>
+#include <math.h>
 
 #include "tabe.h"
 
