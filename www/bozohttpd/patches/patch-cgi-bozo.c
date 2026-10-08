$NetBSD: patch-cgi-bozo.c,v 1.1 2014/01/07 19:35:28 jperkin Exp $

SunOS does not have paths.h

--- cgi-bozo.c.orig	2026-05-03 21:54:07.000000000 +0000
+++ cgi-bozo.c
@@ -39,7 +39,9 @@
 
 #include <ctype.h>
 #include <errno.h>
+#ifndef __sun
 #include <paths.h>
+#endif
 #include <signal.h>
 #include <stdlib.h>
 #include <string.h>
@@ -607,6 +609,9 @@ bozo_process_cgi(bozo_httpreq_t *request)
 		close(sv[1]);
 		closelog();
 		bozo_daemon_closefds(httpd);
+
+		if (httpd->cgibin && chdir(httpd->cgibin) == -1)
+			bozoerr(httpd, 1, "failed to chdir(2)");
 
 		if (-1 == execve(path, argv, envp)) {
 			int saveerrno = errno;
