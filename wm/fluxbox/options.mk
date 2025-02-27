# $NetBSD: options.mk,v 1.8 2020/09/20 13:30:45 nia Exp $

PKG_OPTIONS_VAR=	PKG_OPTIONS.fluxbox
PKG_SUPPORTED_OPTIONS=	imlib2 xft2 xrender
PKG_SUGGESTED_OPTIONS=	xft2 xrender

PKG_OPTIONS_LEGACY_OPTS+=	xft:xft2

.include "../../mk/bsd.options.mk"

.if !empty(PKG_OPTIONS:Mimlib2)
CONFIGURE_ARGS+=	--enable-imlib2
.include "../../graphics/imlib2/buildlink3.mk"
.else
CONFIGURE_ARGS+=	--disable-imlib2
.endif

.if !empty(PKG_OPTIONS:Mxft2)
CONFIGURE_ARGS+=	--enable-xft
.include "../../x11/libXft/buildlink3.mk"
.else
CONFIGURE_ARGS+=	--disable-xft
.endif

.if !empty(PKG_OPTIONS:Mxrender)
CONFIGURE_ARGS+=	--enable-xrender
.include "../../x11/libXrender/buildlink3.mk"
.else
CONFIGURE_ARGS+=	--disable-xrender
.endif
