$NetBSD$

* Fix build with curl-8.16.0.

--- Source/cmCurl.cxx.orig	2025-10-01 15:59:08.860498673 +0000
+++ Source/cmCurl.cxx
@@ -170,7 +170,7 @@ std::string cmCurlSetNETRCOption(::CURL*
                                  const std::string& netrc_file)
 {
   std::string e;
-  CURL_NETRC_OPTION curl_netrc_level = CURL_NETRC_LAST;
+  long curl_netrc_level = CURL_NETRC_LAST;
   ::CURLcode res;
 
   if (!netrc_level.empty()) {
