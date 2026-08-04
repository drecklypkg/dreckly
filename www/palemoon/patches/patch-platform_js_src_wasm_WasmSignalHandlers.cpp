$NetBSD$

Fix build on newer NetBSD versions.

--- platform/js/src/wasm/WasmSignalHandlers.cpp.orig	2026-08-04 14:05:57.629523929 +0000
+++ platform/js/src/wasm/WasmSignalHandlers.cpp
@@ -174,7 +174,12 @@ class AutoSetHandlingSegFault
 #  define RFP_sig(p) ((p)->uc_mcontext.__gregs[22])
 # endif
 #elif defined(__NetBSD__)
-# define XMM_sig(p,i) (((struct fxsave64*)(p)->uc_mcontext.__fpregs)->fx_xmm[i])
+# include <sys/param.h>
+# if __NetBSD_Prereq__(11,0,0)
+#  define XMM_sig(p,i) (((struct fxsave64 *)(p)->uc_mcontext.__fpregs.__fxsave)->fx_xmm[i])
+# else
+#  define XMM_sig(p,i) (((struct fxsave64*)(p)->uc_mcontext.__fpregs)->fx_xmm[i])
+# endif
 # define EIP_sig(p) ((p)->uc_mcontext.__gregs[_REG_EIP])
 # define RIP_sig(p) ((p)->uc_mcontext.__gregs[_REG_RIP])
 # define RAX_sig(p) ((p)->uc_mcontext.__gregs[_REG_RAX])
