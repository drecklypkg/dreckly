$NetBSD: patch-lib_randutils.c,v 1.6 2021/07/25 04:00:34 dholland Exp $

O_CLOEXEC is not available on every platform (e.g. MacOS X < 10.7). It
was introduced in POSIX 2008.
Rename random_get_bytes to avoid symbol name conflict on Solaris.
Include <sys/syscall.h> only when available.

--- lib/randutils.c.orig	2018-06-21 09:58:10.352568488 +0000
+++ lib/randutils.c
@@ -13,7 +13,9 @@
 #include <string.h>
 #include <sys/time.h>
 
+#ifdef HAVE_SYS_SYSCALL_H
 #include <sys/syscall.h>
+#endif
 
 #include "c.h"
 #include "randutils.h"
@@ -74,6 +76,10 @@ static void crank_random(void)
 		rand();
 }
 
+#if !defined(O_CLOEXEC)
+#define O_CLOEXEC 0
+#endif
+
 int random_get_fd(void)
 {
 	int i, fd;
@@ -98,7 +104,7 @@ int random_get_fd(void)
 #define UL_RAND_READ_ATTEMPTS	8
 #define UL_RAND_READ_DELAY	125000	/* microseconds */
 
-void random_get_bytes(void *buf, size_t nbytes)
+void my_random_get_bytes(void *buf, size_t nbytes)
 {
 	unsigned char *cp = (unsigned char *)buf;
 	size_t i, n = nbytes;
@@ -213,7 +219,7 @@ int main(int argc, char *argv[])
 
 	printf("Multiple random calls:\n");
 	for (i = 0; i < n; i++) {
-		random_get_bytes(&v, sizeof(v));
+		my_random_get_bytes(&v, sizeof(v));
 		printf("#%02zu: %25"PRIu64"\n", i, v);
 	}
 
@@ -224,7 +230,7 @@ int main(int argc, char *argv[])
 	if (!buf)
 		err(EXIT_FAILURE, "failed to allocate buffer");
 
-	random_get_bytes(buf, bufsz);
+	my_random_get_bytes(buf, bufsz);
 	for (i = 0; i < n; i++) {
 		vp = (int64_t *) (buf + (i * sizeof(*vp)));
 		printf("#%02zu: %25"PRIu64"\n", i, *vp);
