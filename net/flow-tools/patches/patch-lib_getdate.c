$NetBSD$

Fix implicit declaration of strcmp(3).

--- lib/getdate.c.orig	2026-03-20 09:40:22.484476174 +0000
+++ lib/getdate.c
@@ -53,6 +53,7 @@
 #include "ftlib.h"
 
 #include <stdlib.h>
+#include <string.h>
 #include <ctype.h>
 
 #if defined (STDC_HEADERS) || (!defined (isascii) && !defined (HAVE_ISASCII))
