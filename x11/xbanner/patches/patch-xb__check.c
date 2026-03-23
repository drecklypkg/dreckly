$NetBSD$

Fix build on FreeBSD, which has isnumber(3).

--- xb_check.c.orig	2026-03-23 10:36:17.981411661 +0000
+++ xb_check.c
@@ -145,7 +145,7 @@ char *elem(char *s, int elnum)
 }
 
 /* boolean that checks if a string is numeric */
-int isnumber(char *s)
+int my_isnumber(char *s)
 {
   if(atoi(s)==0 && *s!='0')
     return 0;
@@ -160,6 +160,8 @@ int isnumber(char *s)
   return 1;
 }
 
+#define isnumber my_isnumber
+
 /* return true if the resource is a color resource */
 int iscolorres(int i)
 {
