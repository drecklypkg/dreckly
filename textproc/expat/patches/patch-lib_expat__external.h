$NetBSD$

Keep the code compatible with GCC 4.x by disabling deprecation
warnings.

--- lib/expat_external.h.orig	2026-10-15 15:51:34.574764340 +0000
+++ lib/expat_external.h
@@ -128,7 +128,7 @@
 
 /* Marks a function that Expat still provides but that callers should move off
    of. */
-#  if defined(__clang__) || defined(__GNUC__)
+#  if defined(__clang__)
 #    define XML_ATTR_DEPRECATED(message)                                       \
       __attribute__((__deprecated__(message)))
 #  elif defined(_MSC_VER)
