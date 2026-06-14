$NetBSD$

Fix implicit declaration of strcat(3).

--- etm.c.orig	2026-06-14 18:15:49.030813429 +0000
+++ etm.c
@@ -85,6 +85,7 @@
 # if defined(__STDC__) || defined(SYSV)
 #  if defined(__STDC__)
 #   include	<stdlib.h>
+#   include	<string.h>
 #  else /* SYSV */
 #   include	<malloc.h>
 #  endif /* __STDC__ vs. SYSV */
