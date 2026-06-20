$NetBSD$

Fix implicit int, which modern GCC no longer likes.

--- pddet.c.orig	2026-06-20 01:05:43.757065060 +0000
+++ pddet.c
@@ -274,6 +274,7 @@ int adeltl(a,b)
  else if (a->delta > b->delta) return(1);
  else return(0);}
 
+int
 main(argc,argv)
      int argc;
      char **argv;
