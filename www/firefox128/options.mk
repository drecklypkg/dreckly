# $NetBSD: options.mk,v 1.46 2021/02/08 12:26:20 ryoon Exp $

PKG_OPTIONS_VAR=	PKG_OPTIONS.firefox

PKG_SUPPORTED_OPTIONS+=	dbus webrtc

.include "../../mk/bsd.fast.prefs.mk"

.if ${OPSYS} != "Darwin"
PKG_SUPPORTED_OPTIONS+=	pulseaudio
PKG_SUGGESTED_OPTIONS+=	dbus
.endif

PKG_SUPPORTED_OPTIONS.Linux+=	alsa
PKG_SUGGESTED_OPTIONS.Linux+=	alsa webrtc
PKG_SUGGESTED_OPTIONS.NetBSD+=	webrtc

.include "../../mk/bsd.options.mk"

.if ${OPSYS} != "Darwin"
.  if !empty(PKG_OPTIONS:Malsa)
CONFIGURE_ARGS+=	--enable-alsa
.    include "../../audio/alsa-lib/buildlink3.mk"
.  else
CONFIGURE_ARGS+=	--disable-alsa
.  endif

.  if !empty(PKG_OPTIONS:Mpulseaudio)
CONFIGURE_ARGS+=	--enable-pulseaudio
.    include "../../audio/pulseaudio/buildlink3.mk"
.  else
CONFIGURE_ARGS+=	--disable-pulseaudio
.  endif
.endif

.if !empty(PKG_OPTIONS:Mdbus)
CONFIGURE_ARGS+=	--enable-dbus
.  include "../../sysutils/dbus-glib/buildlink3.mk"
.else
CONFIGURE_ARGS+=	--disable-dbus
.endif

.if !empty(PKG_OPTIONS:Mwebrtc)
CFLAGS+=		-DWEBRTC_POSIX=1
.  include "../../graphics/libv4l/buildlink3.mk"
CONFIGURE_ARGS+=	--enable-webrtc
.else
CONFIGURE_ARGS+=	--disable-webrtc
.endif
