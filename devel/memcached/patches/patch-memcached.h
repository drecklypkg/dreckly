$NetBSD$

Fix duplicate typedef in order to build with gcc4.

--- memcached.h.orig	2025-10-11 19:32:04.125584376 +0000
+++ memcached.h
@@ -697,12 +697,12 @@ typedef void (*io_queue_cb)(io_pending_t
 // IO pending objects are created and stacked into this structure. They are
 // then sent off to remote threads.
 // The objects are returned one at a time to the worker threads.
-typedef struct io_queue_s {
+struct io_queue_s {
     void *ctx; // untouched ptr for specific context
     iop_head_t stack;
     io_queue_stack_cb submit_cb; // callback given a full stack of pending IO's at once.
     int type;
-} io_queue_t;
+};
 
 struct thread_notify {
     struct event notify_event;  /* listen event for notify pipe or eventfd */
