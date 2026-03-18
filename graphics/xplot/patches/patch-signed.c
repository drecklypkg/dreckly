$NetBSD$

Fix implicit declaration of isdigit(3).

--- signed.c.orig	2026-03-18 14:31:38.332797258 +0000
+++ signed.c
@@ -32,6 +32,7 @@ to preserve same.
 */
 #include "xplot.h"
 #include <stdio.h>
+#include <ctype.h>
 
 char *signed_unparse(coord c)
 {
