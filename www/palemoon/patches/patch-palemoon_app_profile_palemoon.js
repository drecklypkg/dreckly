$NetBSD: patch-palemoon_app_profile_palemoon.js,v 1.3 2024/08/03 08:54:26 nia Exp $

Modify some defaults to provide a better initial experience on NetBSD.

--- palemoon/app/profile/palemoon.js.orig	2026-09-14 07:01:16.000000000 +0000
+++ palemoon/app/profile/palemoon.js
@@ -1278,3 +1278,13 @@ pref("status4evar.status.popup.mouseMirror", true);
 
 pref("status4evar.status.popup.invertMirror", false);
 pref("status4evar.status.popup.mouseMirror", true);
+
+// ** pkgsrc specific preferences **
+
+// Otherwise handshake fails on some sites,
+// see various posts on the pale moon forums
+pref("security.tls.hello_downgrade_check", false);
+
+// https://forum.palemoon.org/viewtopic.php?f=5&t=33765
+// Remove workaround after Pale Moon 35.0.1.
+pref("layout.css.has-pseudo.enabled", false);
