# $NetBSD: options.mk,v 1.2 2019/08/30 17:48:07 nia Exp $

PKG_OPTIONS_VAR=	PKG_OPTIONS.aranym
PKG_SUPPORTED_OPTIONS=	opengl aranym-mmu

.include "../../mk/bsd.fast.prefs.mk"

PKG_SUGGESTED_OPTIONS.NetBSD+=	aranym-mmu
PKG_SUGGESTED_OPTIONS.Linux+=	aranym-mmu

.include "../../mk/bsd.options.mk"

.if !empty(PKG_OPTIONS:Mopengl)
CONFIGURE_ARGS+=	--enable-opengl
.include "../../graphics/MesaLib/buildlink3.mk"
.else
CONFIGURE_ARGS+=	--disable-opengl
.endif

PLIST_VARS+=		mmu nommu

.if !empty(PKG_OPTIONS:Maranym-mmu)
PLIST.mmu=		yes
CONFIGURE_ARGS+=	--enable-fullmmu
CONFIGURE_ARGS+=	--enable-fpe=mpfr
.include "../../math/mpfr/buildlink3.mk"
.else
PLIST.nommu=		yes
CONFIGURE_ARGS+=	--disable-fullmmu
CONFIGURE_ARGS+=	--enable-fpe=uae
.endif
