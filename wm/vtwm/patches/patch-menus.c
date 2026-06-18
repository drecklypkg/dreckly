$NetBSD$

Add missing include for wait4(2) to avoid implicit function
declarations.

--- menus.c.orig	2026-06-18 19:05:18.229374266 +0000
+++ menus.c
@@ -37,6 +37,7 @@
 
 #include <X11/Xmu/CharSet.h>
 #include <X11/Xos.h>
+#include <sys/wait.h>
 #ifndef NO_REGEX_SUPPORT
 #include <sys/types.h>
 #include <regex.h>
