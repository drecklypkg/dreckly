$NetBSD: patch-src_data_memory__chunk.cc,v 1.1 2023/11/06 11:26:45 nia Exp $

Remove bogus madvise() forward prototype.

--- src/data/memory_chunk.cc.orig	2025-01-01 12:58:24.000000000 +0000
+++ src/data/memory_chunk.cc
@@ -44,14 +44,6 @@
 #include "torrent/exceptions.h"
 #include "memory_chunk.h"
 
-#ifdef __sun__
-extern "C" int madvise(void *, size_t, int);
-//#include <sys/mman.h>
-//Should be the include line instead, but Solaris
-//has an annoying bug wherein it doesn't declare
-//madvise for C++.
-#endif
-
 namespace torrent {
 
 uint32_t MemoryChunk::m_pagesize = getpagesize();
