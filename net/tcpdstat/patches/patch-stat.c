$NetBSD$

Need to include <string.h> for strcmp(3).

--- stat.c.orig	2026-06-20 10:16:27.448417486 +0000
+++ stat.c
@@ -37,6 +37,7 @@
 
 #include <stdio.h>
 #include <stdlib.h>
+#include <string.h>
 #include <unistd.h>
 #include <signal.h>
 #include <math.h>
