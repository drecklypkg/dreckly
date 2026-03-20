$NetBSD$

Fix implicit function declarations.

--- lib/support.c.orig	2026-03-20 09:41:19.612703945 +0000
+++ lib/support.c
@@ -42,6 +42,7 @@
 #include <syslog.h>
 #include <time.h>
 #include <fcntl.h>
+#include <unistd.h>
 
 #if HAVE_STRINGS_H
  #include <strings.h>
