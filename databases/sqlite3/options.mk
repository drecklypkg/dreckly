# $NetBSD: options.mk,v 1.8 2024/07/19 17:11:54 riastradh Exp $

PKG_OPTIONS_VAR=		PKG_OPTIONS.sqlite3
PKG_SUPPORTED_OPTIONS=		sqlite3-dbstat fts icu deserialize
PKG_SUGGESTED_OPTIONS=		fts # enabled in NetBSD builtin version

.include "../../mk/bsd.options.mk"

.if !empty(PKG_OPTIONS:Msqlite3-dbstat)
CFLAGS+=	-DSQLITE_ENABLE_DBSTAT_VTAB=1
.endif

.if !empty(PKG_OPTIONS:Mfts)
CONFIGURE_ARGS+=	--fts3
CONFIGURE_ARGS+=	--fts4
CONFIGURE_ARGS+=	--fts5
.endif

.if !empty(PKG_OPTIONS:Micu)
CONFIGURE_ARGS+=	--icu-collations
CONFIGURE_ARGS+=	--with-icu-cflags=-I${BUILDLINK_PREFIX.icu}/include
CONFIGURE_ARGS+=	--with-icu-ldflags="-licui18n -licuuc -licudata"
.include "../../textproc/icu/buildlink3.mk"
.endif

.if !empty(PKG_OPTIONS:Mdeserialize)
CFLAGS+=	-DSQLITE_ENABLE_DESERIALIZE=1
.endif
