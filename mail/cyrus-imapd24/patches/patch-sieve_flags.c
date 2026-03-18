$NetBSD$

Fix implicit declaration of string functions.

--- sieve/flags.c.orig	2026-03-18 16:30:48.931068683 +0000
+++ sieve/flags.c
@@ -5,6 +5,7 @@
  *      Author: James Cassell
  */
 
+#include <string.h>
 #include "flags.h"
 #include "imparse.h"
 #include "strarray.h"
