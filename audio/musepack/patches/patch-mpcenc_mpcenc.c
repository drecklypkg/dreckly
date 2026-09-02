$NetBSD$

Fix implicit function declarations.

Fix incompatible pointer type warnings, fatal with gcc14
(from RavenPorts)

--- mpcenc/mpcenc.c.orig	2009-08-26 20:39:06.000000000 +0000
+++ mpcenc/mpcenc.c
@@ -23,6 +23,7 @@
 #include <memory.h>
 #include <time.h>
 #include <errno.h>
+#include <string.h>
 
 #include "mpcenc.h"
 #include <mpc/mpcmath.h>
@@ -689,20 +690,20 @@ Quantisierung ( PsyModel * m,
 
         if ( *resL > 0 ) {
             if ( m->NS_Order_L [Band] > 0 ) {
-                QuantizeSubbandWithNoiseShaping ( subq[Band].L, subx[Band].L, *resL, errorL [Band], m->FIR_L [Band] );
+                QuantizeSubbandWithNoiseShaping ((unsigned int *) subq[Band].L, subx[Band].L, *resL, errorL [Band], m->FIR_L [Band] );
                 memcpy ( errorL [Band], errorL[Band] + 36, MAX_NS_ORDER * sizeof (**errorL) );
             } else {
-				QuantizeSubband                 ( subq[Band].L, subx[Band].L, *resL, errorL [Band], MAX_NS_ORDER );
+				QuantizeSubband ((unsigned int *) subq[Band].L, subx[Band].L, *resL, errorL [Band], MAX_NS_ORDER );
                 memcpy ( errorL [Band], errorL[Band] + 36, MAX_NS_ORDER * sizeof (**errorL) );
             }
         }
 
         if ( *resR > 0 ) {
             if ( m->NS_Order_R [Band] > 0 ) {
-                QuantizeSubbandWithNoiseShaping ( subq[Band].R, subx[Band].R, *resR, errorR [Band], m->FIR_R [Band] );
+                QuantizeSubbandWithNoiseShaping ((unsigned int *) subq[Band].R, subx[Band].R, *resR, errorR [Band], m->FIR_R [Band] );
                 memcpy ( errorR [Band], errorR [Band] + 36, MAX_NS_ORDER * sizeof (**errorL) );
             } else {
-				QuantizeSubband                 ( subq[Band].R, subx[Band].R, *resR, errorL [Band], MAX_NS_ORDER);
+				QuantizeSubband ((unsigned int *) subq[Band].R, subx[Band].R, *resR, errorL [Band], MAX_NS_ORDER);
                 memcpy ( errorR [Band], errorR [Band] + 36, MAX_NS_ORDER * sizeof (**errorL) );
             }
         }
