# $NetBSD: options.mk,v 1.2 2021/06/11 20:14:37 gutteridge Exp $

PKG_OPTIONS_VAR=	PKG_OPTIONS.blackbox
PKG_SUPPORTED_OPTIONS=	xft2
PKG_SUGGESTED_OPTIONS=	xft2

.include "../../mk/bsd.prefs.mk"

# This package was previously named blackbox70.
.if defined(PKG_OPTIONS.blackbox70)
PKG_LEGACY_OPTIONS+=	${PKG_OPTIONS.blackbox70}
PKG_OPTIONS_DEPRECATED_WARNINGS+=	\
	"Deprecated variable PKG_OPTIONS.blackbox70 used, use "${PKG_OPTIONS_VAR:Q}" instead."
.endif

.include "../../mk/bsd.options.mk"

.if !empty(PKG_OPTIONS:Mxft2)
CONFIGURE_ARGS+=	--enable-xft
.include "../../x11/libXft/buildlink3.mk"
.else
CONFIGURE_ARGS+=	--disable-xft
.endif
