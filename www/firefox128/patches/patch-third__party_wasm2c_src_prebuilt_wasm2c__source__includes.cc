$NetBSD$

BSD-style systems don't have alloca.h.

--- third_party/wasm2c/src/prebuilt/wasm2c_source_includes.cc.orig	2025-03-12 11:11:51.844774107 +0000
+++ third_party/wasm2c/src/prebuilt/wasm2c_source_includes.cc
@@ -20,13 +20,13 @@ R"w2c_template(#include <malloc.h>
 )w2c_template"
 R"w2c_template(#define alloca _alloca
 )w2c_template"
-R"w2c_template(#elif defined(__FreeBSD__) || defined(__OpenBSD__)
+R"w2c_template(#elif defined(__sun) || defined(__linux)
 )w2c_template"
-R"w2c_template(#include <stdlib.h>
+R"w2c_template(#include <alloca.h>
 )w2c_template"
 R"w2c_template(#else
 )w2c_template"
-R"w2c_template(#include <alloca.h>
+R"w2c_template(#include <stdlib.h>
 )w2c_template"
 R"w2c_template(#endif
 )w2c_template"
