$NetBSD$

Fix implicit declaration of putenv.

--- tests/at-spi2-atk/atk_test_util.c.orig	2026-01-09 20:56:09.998290831 +0000
+++ tests/at-spi2-atk/atk_test_util.c
@@ -21,6 +21,7 @@
  */
 
 #include "atk_test_util.h"
+#include <stdlib.h>
 #include <signal.h>
 
 static AtspiEventListener *fixture_listener = NULL;
