$NetBSD$

Include <sys/syscall.h> only when available.

--- lib/cpuset.c.orig	2025-02-13 12:24:47.110089304 +0000
+++ lib/cpuset.c
@@ -20,7 +20,9 @@
 #include <errno.h>
 #include <string.h>
 #include <ctype.h>
+#ifdef HAVE_SYS_SYSCALL_H
 #include <sys/syscall.h>
+#endif
 
 #include "cpuset.h"
 #include "c.h"
