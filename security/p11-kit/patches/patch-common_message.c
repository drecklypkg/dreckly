$NetBSD: patch-common_message.c,v 1.3 2024/04/02 02:13:01 charlotte Exp $

Set proper version to have the "locale_t" identifier.

On DragonFly, xlocale.h provides all the locale functionality (locale.h
provides only some of it).

--- common/message.c.orig	2023-10-24 12:58:49.000000000 +0000
+++ common/message.c
@@ -41,7 +41,7 @@
  * Oh god. glibc is nasty. Changes behavior and definitions of POSIX
  * functions to completely different signatures depending on defines
  */
-#define _POSIX_C_SOURCE 200112L
+#define _POSIX_C_SOURCE 200809L
 
 #include "compat.h"
 #define P11_DEBUG_FLAG P11_DEBUG_LIB
@@ -51,7 +51,11 @@
 #include <assert.h>
 #include <errno.h>
 #ifdef HAVE_LOCALE_H
+#ifdef __DragonFly__
+#include <xlocale.h>
+#else
 #include <locale.h>
+#endif // __DragonFly__
 #endif
 #include <stdarg.h>
 #include <stdlib.h>
