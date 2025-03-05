$NetBSD$

Fix build on OpenBSD, via OpenBSD Ports.

--- common/unix-peer.c.orig	2025-03-05 14:41:38.987920079 +0000
+++ common/unix-peer.c
@@ -55,7 +55,11 @@ p11_get_upeer_id (int cfd, uid_t *uid, u
 {
 	int ret;
 #if defined(SO_PEERCRED)
+#ifndef __OpenBSD__
 	struct ucred cr;
+#else
+	struct sockpeercred cr;
+#endif
 	socklen_t cr_len;
 
 	cr_len = sizeof (cr);
