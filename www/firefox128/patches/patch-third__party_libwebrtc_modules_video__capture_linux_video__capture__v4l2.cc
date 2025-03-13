$NetBSD$

* Fix build under NetBSD 9 and older.
  The older NetBSD's sys/videoio.h does not have v4l2_capability.device_caps.

--- third_party/libwebrtc/modules/video_capture/linux/video_capture_v4l2.cc.orig	2025-02-24 16:55:04.000000000 +0000
+++ third_party/libwebrtc/modules/video_capture/linux/video_capture_v4l2.cc
@@ -86,6 +86,7 @@ int32_t VideoCaptureModuleV4L2::Init(con
     if ((fd = open(device, O_RDONLY)) != -1) {
       // query device capabilities
       struct v4l2_capability cap;
+#if defined(VIDIOC_QUERYCAP)
       if (ioctl(fd, VIDIOC_QUERYCAP, &cap) == 0) {
         if (cap.bus_info[0] != 0) {
           if (strncmp((const char*)cap.bus_info,
@@ -98,6 +99,7 @@ int32_t VideoCaptureModuleV4L2::Init(con
           }
         }
       }
+#endif
       close(fd);  // close since this is not the matching device
     }
   }
