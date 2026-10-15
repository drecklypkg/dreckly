$NetBSD$

Fix USE_AVX512 logic.

--- cipher/blake2.c.orig	2025-02-26 12:03:24.332576410 +0000
+++ cipher/blake2.c
@@ -830,7 +830,7 @@ static gcry_err_code_t blake2s_init_ctx(
 #ifdef USE_AVX
   c->use_avx = !!(features & HWF_INTEL_AVX);
 #endif
-#ifdef USE_AVX
+#ifdef USE_AVX512
   c->use_avx512 = !!(features & HWF_INTEL_AVX512);
 #endif
 
