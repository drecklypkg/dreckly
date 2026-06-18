$NetBSD: patch-xmix.c,v 1.1 2019/07/16 10:46:45 micha Exp $

- support more OSes
- fix void main
- remove debug printout

--- xmix.c.orig	2026-06-18 19:29:24.745505748 +0000
+++ xmix.c
@@ -48,8 +48,11 @@ to Rick! I'll call this version V2.1
 
 ======================================================================*/
 
+#include <sys/ioctl.h>
+#include <sys/soundcard.h>
 #include <stdio.h>
-#include <sys/errno.h>
+#include <stdlib.h>
+#include <errno.h>
 #include <fcntl.h>
 
 /*
@@ -77,8 +80,6 @@ to Rick! I'll call this version V2.1
 #include "square_empty.bit"
 #include "square_with_x.bit"
 
-#include <linux/soundcard.h>
-
 #define SOUND_FULL_SCALE 100.0
 #define MAX_SOUND_VOL 95
 #define MIN_SOUND_VOL 05
@@ -450,7 +451,7 @@ static void set_supported(VolumeControl *vcptr, int is
 }
 
 
-void main (int argc, char **argv)
+int main (int argc, char **argv)
 {
   XtAppContext app_context;
   int scroll_sep, longway;
@@ -742,7 +743,7 @@ void main (int argc, char **argv)
   mic.locked = 0;
   reclvl.locked = 0;
 
-  printf("supported = 0x%x\n",supported);
+  /*printf("supported = 0x%x\n",supported);*/
   set_supported(&master,(supported & SOUND_MASK_VOLUME) != 0);
   set_supported(&bass,(supported & SOUND_MASK_BASS) != 0);
   set_supported(&treble,(supported & SOUND_MASK_TREBLE) != 0);
