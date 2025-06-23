# $NetBSD$

DISTNAME=	oils-for-unix-0.31.0
CATEGORIES=	shells
MASTER_SITES=	https://oils.pub/download/

MAINTAINER=	marc@coquand.email
HOMEPAGE=	https://oils.pub/download/
COMMENT=	Oils is a Unix shell with JSON-compatible structured data. 
LICENSE=	apache-2.0

GNU_CONFIGURE=	yes
USE_LANGUAGES=	c c++

PKG_SHELL=	/bin/osh
PKG_SHELL+=	/bin/ysh

PKG_OPTIONS_VAR=	PKG_OPTIONS.oils-for-unix
PKG_SUPPORTED_OPTIONS=	readline

.include "../../mk/bsd.options.mk"

.if !empty(PKG_OPTIONS:Mreadline)
.if ${OPSYS} == "OpenBSD"
BUILDLINK_TRANSFORM+= l:readline:ereadline:ehistory
.endif
.include "../../devel/readline/buildlink3.mk"
CONFIGURE_ARGS+=		--with-readline
READLINE_DIR=			${BUILDLINK_PREFIX.readline}
CONFIGURE_ARGS+=		--readline ${READLINE_DIR}
.endif

do-build:
	cd ${WRKSRC} && _build/oils.sh

do-install:
	cd ${WRKSRC} && DESTDIR=${DESTDIR} ./install

.include "../../mk/bsd.pkg.mk"
