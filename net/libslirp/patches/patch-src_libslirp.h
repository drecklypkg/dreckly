$NetBSD$

For some reason FreeBSD defiles AF_INET6 in <sys/socket.h>.

--- src/libslirp.h.orig	2025-03-02 12:05:26.270555064 +0000
+++ src/libslirp.h
@@ -11,6 +11,7 @@
 #include <ws2tcpip.h>
 #include <in6addr.h>
 #else
+#include <sys/socket.h>
 #include <netinet/in.h>
 #include <arpa/inet.h>
 #endif
