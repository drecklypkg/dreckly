$NetBSD: patch-common_dialog.c,v 1.1 2013/09/10 18:24:10 joerg Exp $

--- common/dialog.c.orig	1996-04-30 07:02:36.000000000 +0000
+++ common/dialog.c
@@ -45,8 +45,10 @@ static char copyright[] =
 #include "cdefs.h"
 #include "global.h"
 #include <stdio.h>
+#include <string.h>
 #include <fcntl.h>
 #include <syslog.h>
+#include <sys/ioctl.h>
 #include "mcap.h"
 #include "ttio.h"
 
