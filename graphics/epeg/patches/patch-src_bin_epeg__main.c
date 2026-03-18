$NetBSD$

Fix implicit function declarations.

--- src/bin/epeg_main.c.orig	2026-03-18 09:23:05.770635625 +0000
+++ src/bin/epeg_main.c
@@ -1,3 +1,5 @@
+#include <stdio.h>
+#include <stdlib.h>
 #include "epeg_main.h"
 
 /* main */
