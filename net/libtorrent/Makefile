# $NetBSD: Makefile,v 1.65 2024/10/04 09:00:05 adam Exp $

DISTNAME=	libtorrent-0.15.1
CATEGORIES=	net
MASTER_SITES=	${MASTER_SITE_GITHUB:=rakshasa/}
GITHUB_TAG=	v${PKGVERSION_NOREV}

MAINTAINER=	pkgsrc-users@NetBSD.org
HOMEPAGE=	https://github.com/rakshasa/libtorrent
COMMENT=	BitTorrent library written in C++
LICENSE=	gnu-gpl-v2

USE_LANGUAGES=		c c++
USE_CXX_FEATURES+=	c++14
USE_LIBTOOL=		yes
USE_TOOLS+=		autoconf automake autoreconf gmake pkg-config

GNU_CONFIGURE=		yes
CONFIGURE_ARGS+=	--disable-debug

CONFIGURE_ARGS.OpenBSD+=	--disable-mincore

pre-configure:
	${RUN} cd ${WRKSRC} && autoreconf -fiv

.include "../../devel/zlib/buildlink3.mk"
.include "../../security/openssl/buildlink3.mk"
.include "../../mk/bsd.pkg.mk"
