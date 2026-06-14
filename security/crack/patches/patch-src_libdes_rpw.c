$NetBSD$

Fix implicit declaration of exit(3).

--- src/libdes/rpw.c.orig	2026-06-14 15:26:04.064831749 +0000
+++ src/libdes/rpw.c
@@ -46,6 +46,7 @@
  */
 
 #include <stdio.h>
+#include <stdlib.h>
 #include "des.h"
 
 int main(argc,argv)
