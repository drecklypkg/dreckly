$NetBSD$

Fix incorrect ctype usage. This causes a segfault on startup on
netbsd-11.

--- SP/code/ui/ui_shared.c.orig	2026-04-27 20:59:14.563522726 +0000
+++ SP/code/ui/ui_shared.c
@@ -296,7 +296,7 @@ static unsigned hashForString(const char *str) {
 	hash = 0;
 	i = 0;
 	while ( str[i] != '\0' ) {
-		letter = tolower( str[i] );
+		letter = tolower( (unsigned char)str[i] );
 		hash += (unsigned)( letter ) * ( i + 119 );
 		i++;
 	}
