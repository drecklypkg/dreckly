$NetBSD$

Fix implicit declaration of memset(3).

--- Output/solaris/Sun.h.orig	2026-03-23 12:23:58.230974725 +0000
+++ Output/solaris/Sun.h
@@ -32,6 +32,7 @@
 #include <stropts.h>
 
 #include <stdlib.h>
+#include <string.h>
 #include <stdio.h>
 
 #include "xmms/plugin.h"
