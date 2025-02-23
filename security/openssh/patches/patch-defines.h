$NetBSD$

Define ROOTUID, UTMPX_FILE and WTMPX_FILE

--- defines.h.orig	2025-02-18 08:15:08.000000000 +0000
+++ defines.h
@@ -821,6 +821,24 @@ struct winsize {
 #    endif
 #  endif
 #endif
+#ifndef UTMPX_FILE
+#  ifdef _PATH_UTMPX
+#    define UTMPX_FILE _PATH_UTMPX
+#  else
+#    ifdef CONF_UTMPX_FILE
+#      define UTMPX_FILE CONF_UTMPX_FILE
+#    endif
+#  endif
+#endif
+#ifndef WTMPX_FILE
+#  ifdef _PATH_WTMPX
+#    define WTMPX_FILE _PATH_WTMPX
+#  else
+#    ifdef CONF_WTMPX_FILE
+#      define WTMPX_FILE CONF_WTMPX_FILE
+#    endif
+#  endif
+#endif
 /* pick up the user's location for lastlog if given */
 #ifndef LASTLOG_FILE
 #  ifdef _PATH_LASTLOG
