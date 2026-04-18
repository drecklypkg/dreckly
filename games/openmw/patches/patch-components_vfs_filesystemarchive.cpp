$NetBSD$

Fix build with recent GCC.

--- components/vfs/filesystemarchive.cpp.orig	2026-04-18 21:50:21.789137607 +0000
+++ components/vfs/filesystemarchive.cpp
@@ -3,6 +3,7 @@
 #include <boost/filesystem.hpp>
 
 #include <components/debug/debuglog.hpp>
+#include <algorithm>
 
 namespace VFS
 {
