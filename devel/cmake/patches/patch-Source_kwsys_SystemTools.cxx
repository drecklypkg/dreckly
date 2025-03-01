$NetBSD$

Avoid cmake logic that tries to find the shortest path and e.g. converts
/private/tmp -> /tmp, breaking buildlink.

--- Source/kwsys/SystemTools.cxx.orig	2025-03-01 09:02:23.367146089 +0000
+++ Source/kwsys/SystemTools.cxx
@@ -4969,6 +4969,8 @@ void SystemTools::ClassInitialize()
   // Create statics singleton instance
   SystemToolsStatics = new SystemToolsStatic;
 
+  return;
+
 #if KWSYS_SYSTEMTOOLS_USE_TRANSLATION_MAP
 // Add some special translation paths for unix.  These are not added
 // for windows because drive letters need to be maintained.  Also,
