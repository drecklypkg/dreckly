$NetBSD$

Fix implicit function declarations.

--- src/aclyacc.c.orig	2026-03-20 09:44:33.603521121 +0000
+++ src/aclyacc.c
@@ -25,6 +25,10 @@ static int yygrowstack();
 #include "acl2.h"
 #include <stdio.h> /* XXX REMOVE */
 
+static int yylex (void);
+static int yyerror (char *s);
+extern int yyparse (void);
+
 /* XXX remove */
 unsigned char fmt_buf[32];
 unsigned char fmt_buf2[32];
