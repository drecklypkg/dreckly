$NetBSD$

Use portable versions of MIN/MAX.

--- include/haproxy/compat.h.orig	2025-03-18 10:47:13.674077326 +0000
+++ include/haproxy/compat.h
@@ -94,19 +94,11 @@ typedef struct { } empty_t;
 #endif
 
 #ifndef MIN
-#define MIN(a, b) ({				\
-	typeof(a) _a = (a);			\
-	typeof(a) _b = (b);			\
-	((_a < _b) ? _a : _b);			\
-})
+#define MIN(a,b)	(((a) < (b)) ? (a) : (b))
 #endif
 
 #ifndef MAX
-#define MAX(a, b) ({				\
-	typeof(a) _a = (a);			\
-	typeof(a) _b = (b);			\
-	((_a > _b) ? _a : _b);			\
-})
+#define MAX(a,b)	(((a) > (b)) ? (a) : (b))
 #endif
 
 /* this is for libc5 for example */
