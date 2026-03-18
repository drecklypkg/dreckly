$NetBSD$

Fix implicit function declarations.

--- src/mpeg2dec/spatscal.c.orig	2026-03-18 14:12:54.946383579 +0000
+++ src/mpeg2dec/spatscal.c
@@ -1,5 +1,7 @@
 
 #include <stdio.h>
+#include <stdlib.h>
+#include <string.h>
 #include "config.h"
 #include "global.h"
 
