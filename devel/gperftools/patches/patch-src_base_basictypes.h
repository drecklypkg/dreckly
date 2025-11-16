$NetBSD: patch-src_base_basictypes.h,v 1.1 2022/09/18 19:28:23 he Exp $

Add support for NetBSD/powerpc, recognized via __powerpc__.

--- src/base/basictypes.h.orig	2023-08-10 03:46:13.000000000 +0000
+++ src/base/basictypes.h
@@ -368,7 +368,7 @@ class AssignAttributeStartEnd {
 #if defined(HAVE___ATTRIBUTE__)
 # if (defined(__i386__) || defined(__x86_64__))
 #   define CACHELINE_ALIGNED __attribute__((aligned(64)))
-# elif (defined(__PPC__) || defined(__PPC64__))
+# elif (defined(__PPC__) || defined(__PPC64__) || defined(__powerpc__))
 #   define CACHELINE_ALIGNED __attribute__((aligned(16)))
 # elif (defined(__arm__))
 #   define CACHELINE_ALIGNED __attribute__((aligned(64)))
@@ -384,6 +384,8 @@ class AssignAttributeStartEnd {
 #   define CACHELINE_ALIGNED __attribute__((aligned(64)))
 # elif defined(__loongarch64)
 #   define CACHELINE_ALIGNED __attribute__((aligned(64)))
+# elif defined(__sparcv9) || defined(__sparcv9__) 
+#   define CACHELINE_ALIGNED __attribute__((aligned(64)))
 # else
 #   error Could not determine cache line length - unknown architecture
 # endif
