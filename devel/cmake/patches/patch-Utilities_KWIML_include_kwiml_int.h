$NetBSD$

This isn't broken, but cmake thinks it is, so we need to go along.

--- Utilities/KWIML/include/kwiml/int.h.orig	2025-03-01 13:50:50.763416890 +0000
+++ Utilities/KWIML/include/kwiml/int.h
@@ -285,7 +285,7 @@ An includer may test the following macro
 # define KWIML_INT_BROKEN_SCNx8 1
 #endif
 
-#if (defined(__SUNPRO_C)||defined(__SUNPRO_CC)) && defined(_CHAR_IS_UNSIGNED)
+#if (defined(__SUNPRO_C)||defined(__SUNPRO_CC)||defined(__illumos__) && defined(_CHAR_IS_UNSIGNED)
 # define KWIML_INT_BROKEN_INT8_T 1 /* system type defined incorrectly */
 #elif defined(__BORLANDC__) && defined(_CHAR_UNSIGNED)
 # define KWIML_INT_BROKEN_INT8_T 1 /* system type defined incorrectly */
