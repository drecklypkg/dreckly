$NetBSD$

Fix incompatible pointer type warnings, fatal with gcc14
(from RavenPorts)

--- libmpcpsy/ans.c.orig	2026-09-02 08:08:07.460737514 +0000
+++ libmpcpsy/ans.c
@@ -288,12 +288,12 @@ NS_Analyse ( PsyModel* m,
     // for L or M, respectively
     memset ( m->FIR_L,      0, sizeof m->FIR_L      );         // reset FIR
     memset ( m->NS_Order_L, 0, sizeof m->NS_Order_L );         // reset Flags
-	FindOptimalANS ( MaxBand, MSflag, ANSspec_L, ANSspec_M, m->NS_Order_L, m->SNR_comp_L, m->FIR_L, smr.L, smr.M, m->SCF_Index_L, Transient );
+	FindOptimalANS ( MaxBand, MSflag, ANSspec_L, ANSspec_M, m->NS_Order_L, m->SNR_comp_L, m->FIR_L, smr.L, smr.M, (const int (*)[3])m->SCF_Index_L, Transient );
 
     // for R or S, respectively
 	memset ( m->FIR_R,      0, sizeof m->FIR_R      );         // reset FIR
 	memset ( m->NS_Order_R, 0, sizeof m->NS_Order_R );         // reset Flags
-	FindOptimalANS ( MaxBand, MSflag, ANSspec_R, ANSspec_S, m->NS_Order_R, m->SNR_comp_R, m->FIR_R, smr.R, smr.S, m->SCF_Index_R, Transient );
+	FindOptimalANS ( MaxBand, MSflag, ANSspec_R, ANSspec_S, m->NS_Order_R, m->SNR_comp_R, m->FIR_R, smr.R, smr.S, (const int (*)[3])m->SCF_Index_R, Transient );
 
     return;
 }
