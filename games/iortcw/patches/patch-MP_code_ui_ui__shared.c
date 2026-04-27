$NetBSD$

Fix incorrect ctype usage. This causes a segfault on startup on
netbsd-11.

--- MP/code/ui/ui_shared.c.orig	2026-04-27 20:58:50.789255894 +0000
+++ MP/code/ui/ui_shared.c
@@ -224,7 +224,7 @@ static unsigned hashForString(const char *str) {
 	hash = 0;
 	i = 0;
 	while ( str[i] != '\0' ) {
-		letter = tolower( str[i] );
+		letter = tolower( (unsigned char)str[i] );
 		hash += (unsigned)( letter ) * ( i + 119 );
 		i++;
 	}
