$NetBSD$

Fix building without HAS_MESSAGE_WINDOW.

--- src/popupwin.c.orig	2025-10-09 10:23:48.851952926 +0000
+++ src/popupwin.c
@@ -28,6 +28,8 @@ static poppos_entry_T poppos_entries[] =
     {"center", POPPOS_CENTER}
 };
 
+static int popup_on_cmdline = FALSE;
+
 #ifdef HAS_MESSAGE_WINDOW
 // Window used for ":echowindow"
 static win_T *message_win = NULL;
@@ -40,8 +42,6 @@ static int  message_win_time = 3000;
 // hit-enter prompt.
 static int    start_message_win_timer = FALSE;
 
-static int popup_on_cmdline = FALSE;
-
 static void may_start_message_win_timer(win_T *wp);
 #endif
 
