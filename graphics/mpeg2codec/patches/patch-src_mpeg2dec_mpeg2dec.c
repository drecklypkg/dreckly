$NetBSD$

Fix implicit declaration of lseek(2), close(2).

--- src/mpeg2dec/mpeg2dec.c.orig	2026-03-18 14:11:40.756693563 +0000
+++ src/mpeg2dec/mpeg2dec.c
@@ -32,6 +32,7 @@
 #include <stdlib.h>
 #include <ctype.h>
 #include <fcntl.h>
+#include <unistd.h>
 
 #define GLOBAL
 #include "config.h"
