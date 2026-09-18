$NetBSD$

Revert commit 4c346cc711118689b9b6d05495c2fbcf495e5ab0

--- platform/js/src/jsprf.cpp.orig	2026-09-12 13:38:01.000000000 +0000
+++ platform/js/src/jsprf.cpp
@@ -312,13 +312,7 @@ cvt_s(SprintfState* ss, const char* s, int width, int 
         s = generic_null_str(s);
 
     // Limit string length by precision value
-    // We'd want to use strnlen() here, but it is not supported by all targets
-    // (Most notably old OS X), so use memchr instead.
-    // Replace with `size_t slen = strnlen(s, size_t(prec));` once we no longer
-    // need to cater to this.
-    const char* sptr = (const char*)memchr(s, 0, size_t(prec));
-    size_t slen = sptr ? sptr - s : size_t(prec);
-    
+    size_t slen = strnlen(s, size_t(prec));
     if (slen > INT_MAX) {
         return false;
     }
