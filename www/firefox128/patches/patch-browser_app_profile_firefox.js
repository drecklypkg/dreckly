$NetBSD$

Allow system language packs to load by default.

--- browser/app/profile/firefox.js.orig	2025-03-12 14:56:45.190431398 +0000
+++ browser/app/profile/firefox.js
@@ -56,7 +56,7 @@ pref("extensions.systemAddon.update.enab
 
 // Disable add-ons that are not installed by the user in all scopes by default.
 // See the SCOPE constants in AddonManager.sys.mjs for values to use here.
-pref("extensions.autoDisableScopes", 15);
+pref("extensions.autoDisableScopes", 11);
 // Scopes to scan for changes at startup.
 pref("extensions.startupScanScopes", 0);
 
