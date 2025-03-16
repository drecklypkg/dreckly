$NetBSD$

Support aarch64.

--- third_party/rust/libc/src/unix/bsd/netbsdlike/netbsd/other/mod.rs.orig	2025-03-07 15:41:38.959428103 +0000
+++ third_party/rust/libc/src/unix/bsd/netbsdlike/netbsd/other/mod.rs
@@ -1,5 +1,6 @@
 cfg_if! {
     if #[cfg(any(target_arch = "sparc64",
+                 target_arch = "aarch64",
                  target_arch = "x86_64"))] {
         mod b64;
         pub use self::b64::*;
