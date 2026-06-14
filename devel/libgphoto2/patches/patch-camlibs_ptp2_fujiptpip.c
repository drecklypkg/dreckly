$NetBSD$

Include the correct header for inet_aton(3) to avoid an implicit
function declaration.

--- camlibs/ptp2/fujiptpip.c.orig	2026-06-14 18:07:17.855827327 +0000
+++ camlibs/ptp2/fujiptpip.c
@@ -59,6 +59,7 @@
 # include <winsock2.h>
 # include <ws2tcpip.h>
 #else
+# include <arpa/inet.h>
 # include <sys/socket.h>
 # include <netinet/in.h>
 #endif
