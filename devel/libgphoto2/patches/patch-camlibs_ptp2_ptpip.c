$NetBSD$

Include the correct header for inet_aton(3) to avoid an implicit
function declaration.

--- camlibs/ptp2/ptpip.c.orig	2023-08-28 07:46:39.000000000 +0000
+++ camlibs/ptp2/ptpip.c
@@ -48,6 +48,7 @@
 # include <winsock2.h>
 # include <ws2tcpip.h>
 #else
+# include <arpa/inet.h>
 # include <sys/socket.h>
 # include <netinet/in.h>
 # include <fcntl.h>
