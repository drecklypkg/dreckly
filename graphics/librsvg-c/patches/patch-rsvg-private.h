$NetBSD$

Fix building with latest libxml2.

--- rsvg-private.h.orig	2025-07-31 23:36:46.900666186 +0000
+++ rsvg-private.h
@@ -32,6 +32,7 @@
 #include "rsvg.h"
 
 #include <libxml/SAX.h>
+#include <libxml/parser.h>
 #include <libxml/xmlmemory.h>
 #include <pango/pango.h>
 #include <glib.h>
