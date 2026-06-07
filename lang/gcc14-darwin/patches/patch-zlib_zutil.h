$NetBSD$

# Fix build under clang17 on macOS

--- zlib/zutil.h.orig	2024-12-30 10:24:20.000000000 +0000
+++ zlib/zutil.h
@@ -131,6 +131,7 @@ extern z_const char * const z_errmsg[10]
 #endif
 
 #if defined(MACOS) || defined(TARGET_OS_MAC)
+#if __clang_major__ < 17
 #  define OS_CODE  7
 #  ifndef Z_SOLO
 #    if defined(__MWERKS__) && __dest_os != __be_os && __dest_os != __win32_os
@@ -142,6 +143,7 @@ extern z_const char * const z_errmsg[10]
 #    endif
 #  endif
 #endif
+#endif
 
 #ifdef __acorn
 #  define OS_CODE 13
