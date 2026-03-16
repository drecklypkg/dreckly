$NetBSD$

Fix implicit function declaration of malloc.

--- src/bk_edit_dialog_config.c.orig	2003-11-29 13:14:14.000000000 +0000
+++ src/bk_edit_dialog_config.c
@@ -25,6 +25,7 @@
  *
  */
 
+#include <stdlib.h>
 #include <string.h>
 
 #include <gdk/gdk.h>
