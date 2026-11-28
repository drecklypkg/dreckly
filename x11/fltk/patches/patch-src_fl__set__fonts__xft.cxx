$NetBSD$

Fix ctype usage.

ctype(3) toupper: invalid input: -50
Program received signal SIGABRT, Aborted.

(gdb) bt
#0  0x000074a2f20cec5a in _lwp_kill () from /usr/lib/libc.so.12
#1  0x000074a2f20db094 in abort () from /usr/lib/libc.so.12
#2  0x000074a2f20db02a in je_arena_prof_promote () from /usr/lib/libc.so.12
#3  0x000074a2f20ca1da in toupper () from /usr/lib/libc.so.12
#4  0x000074a2f29fb22a in make_raw_name (raw=raw@entry=0x7f7fff602380 " Arial", pretty=<optimized out>)
    at fl_set_fonts_xft.cxx:136
#5  0x000074a2f29fb611 in Fl::set_fonts (pattern_name=pattern_name@entry=0x1e535b "-*-iso10646-1")
    at fl_set_fonts_xft.cxx:324

--- src/fl_set_fonts_xft.cxx.orig	2026-11-28 16:08:25.338264357 +0000
+++ src/fl_set_fonts_xft.cxx
@@ -133,7 +133,7 @@ static void make_raw_name(char *raw, char *pretty)
         style++; // Start of Style string
         if ((style >= last) || (*style == 0)) continue;
       }
-      type = toupper(style[0]);
+      type = toupper((unsigned char)style[0]);
       switch (type)
       {
       // Things we might see: Regular Normal Bold Italic Oblique (??what??) Medium
