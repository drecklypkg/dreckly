$NetBSD$

Fix implicit declaration of exit(3).

--- gifout.c.orig	2026-03-23 09:55:42.925057024 +0000
+++ gifout.c
@@ -44,6 +44,7 @@
  */
 
 #include <stdio.h>
+#include <stdlib.h>
 #include "port.h"
 #include "gifint.h"
 #include "kljcpyrt.h"
