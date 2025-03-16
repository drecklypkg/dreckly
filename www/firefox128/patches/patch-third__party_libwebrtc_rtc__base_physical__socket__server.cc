$NetBSD$

Fix building on NetBSD.

--- third_party/libwebrtc/rtc_base/physical_socket_server.cc.orig	2025-02-24 16:55:04.000000000 +0000
+++ third_party/libwebrtc/rtc_base/physical_socket_server.cc
@@ -770,7 +770,7 @@ int PhysicalSocket::TranslateOption(Opti
       return -1;
 #endif
     case OPT_RECV_ECN:
-#if defined(WEBRTC_POSIX)
+#if defined(WEBRTC_POSIX) && defined(IP_RECVTOS)
       if (family_ == AF_INET6) {
         *slevel = IPPROTO_IPV6;
         *sopt = IPV6_RECVTCLASS;
