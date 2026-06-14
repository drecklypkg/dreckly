$NetBSD$

Fix implicit declaration of exit(3).

--- etmtest.c.orig	2026-06-14 18:18:28.205764697 +0000
+++ etmtest.c
@@ -15,6 +15,7 @@
 # endif
 
 # include	<stdio.h>
+# include	<stdlib.h>
 
 # include	"etm.h"
 
