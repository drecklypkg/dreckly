# $NetBSD$

PKG_OPTIONS_VAR=	PKG_OPTIONS.bochs
PKG_SUPPORTED_OPTIONS+=	sdl x11

.include "../../mk/bsd.fast.prefs.mk"
.if ${OPSYS} != "Darwin"
PKG_SUGGESTED_OPTIONS=	sdl x11
.else
PKG_SUGGESTED_OPTIONS=	sdl
.endif

PLIST_VARS+=		nox11 x11 sdl

.include "../../mk/bsd.options.mk"

# want SDL for sound and portable graphics
.if !empty(PKG_OPTIONS:Msdl)
PLIST.sdl=		yes
CONFIGURE_ARGS+=	--with-sdl
.  include "../../devel/SDL/buildlink3.mk"
.else
CONFIGURE_ARGS+=	--without-sdl
.endif

.if !empty(PKG_OPTIONS:Mx11)
PLIST.x11=			yes
LIBS+=				-lX11
CONFIGURE_ARGS+=		--with-x
CONFIGURE_ARGS+=		--with-x11
BUILDLINK_DEPMETHOD.libXt?=	build
.  include "../../x11/libSM/buildlink3.mk"
.  include "../../x11/libX11/buildlink3.mk"
.  include "../../x11/libXpm/buildlink3.mk"
.  include "../../x11/libXrandr/buildlink3.mk"
.  include "../../x11/libXt/buildlink3.mk"
.else
PLIST.nox11=		yes
.  include "../../mk/curses.buildlink3.mk"
.  if ${OPSYS} == "NetBSD"
.    if ${CURSES_TYPE} == "curses"
GUI_LINK_OPTS_TERM=	-lcurses
.    endif
.  endif
CONFIGURE_ARGS+=	--without-x
CONFIGURE_ARGS+=	--without-x11
CONFIGURE_ARGS+=	--with-term
.endif
