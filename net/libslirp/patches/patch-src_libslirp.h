$NetBSD$

For some reason FreeBSD defiles AF_INET6 in <sys/socket.h>.

--- src/libslirp.h.orig	2026-09-28 13:00:56.753737129 +0000
+++ src/libslirp.h
@@ -25,6 +25,7 @@ typedef ssize_t slirp_ssize_t;
 #else
 #include <sys/types.h>
 typedef ssize_t slirp_ssize_t;
+#include <sys/socket.h>
 #include <netinet/in.h>
 #include <arpa/inet.h>
 #define SLIRP_EXPORT
