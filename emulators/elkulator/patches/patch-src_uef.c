$NetBSD$

gzFile is already a pointer.

--- src/uef.c.orig	2026-02-13 13:26:21.688298594 +0000
+++ src/uef.c
@@ -12,7 +12,7 @@ int reallyfasttapebreak;
 
 int tapelcount,tapellatch,pps;
 int intone=0;
-gzFile *uef;
+gzFile uef;
 int cswena;
 
 int inchunk=0,chunkid=0,chunklen=0;
@@ -256,6 +256,6 @@ void closeuef()
         if (uef)
 	{
            	gzclose(uef);
-		uef=(gzFile *)NULL;
+		uef=NULL;
 	}
 }
