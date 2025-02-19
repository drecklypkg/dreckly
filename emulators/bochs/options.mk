# $NetBSD$

PKG_OPTIONS_VAR=	PKG_OPTIONS.bochs
PKG_SUPPORTED_OPTIONS+=	debug x11
PKG_SUGGESTED_OPTIONS+=	x11

PLIST_VARS+=		nox11 plugins x11

.include "../../mk/bsd.options.mk"

# Debugging features for the client operating systems. These options are
# not enabled by default because they can adversely impact performance.
.if !empty(PKG_OPTIONS:Mdebug)
CONFIGURE_ARGS+=	--disable-plugins
CONFIGURE_ARGS+=	--enable-debugger
CONFIGURE_ARGS+=	--enable-iodebug
CONFIGURE_ARGS+=	--enable-x86-debugger
.else
PLIST.plugins=		yes
CONFIGURE_ARGS+=	--enable-plugins
.endif

.if empty(PKG_OPTIONS:Mx11)
PLIST.nox11=		yes
CONFIGURE_ARGS+=	--without-x
CONFIGURE_ARGS+=	--without-x11
CONFIGURE_ARGS+=	--with-term
CONFIGURE_ARGS+=	--with-sdl
.else
PLIST.x11=		yes
.endif

.if !empty(PKG_OPTIONS:Mdebug) && !empty(PKG_OPTIONS:Mx11)
.include "../../x11/gtk3/buildlink3.mk"
.endif

.if !empty(PKG_OPTIONS:Mx11)
BUILDLINK_DEPMETHOD.libXt?=	build
.  include "../../x11/libSM/buildlink3.mk"
.  include "../../x11/libX11/buildlink3.mk"
.  include "../../x11/libXpm/buildlink3.mk"
.  include "../../x11/libXrandr/buildlink3.mk"
.  include "../../x11/libXt/buildlink3.mk"
.else
.  include "../../mk/curses.buildlink3.mk"
.  if ${OPSYS} == "NetBSD"
.    if ${CURSES_TYPE} == "curses"
GUI_LINK_OPTS_TERM=	-lcurses
.    endif
.  endif
.endif
