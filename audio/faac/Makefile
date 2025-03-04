# $NetBSD: Makefile,v 1.18 2019/11/09 11:48:35 nia Exp $

DISTNAME=	faac-1.31.1
CATEGORIES=	audio
MASTER_SITES=	${MASTER_SITE_GITHUB:=knik0/}
GITHUB_TAG=	${DISTNAME}

MAINTAINER=	pkgsrc-users@NetBSD.org
HOMEPAGE=	https://github.com/knik0/faac
COMMENT=	AAC audio encoder
LICENSE=	gnu-lgpl-v2

USE_LIBTOOL=		yes
USE_TOOLS+=		autoconf autoreconf automake
GNU_CONFIGURE=		yes

PKGCONFIG_OVERRIDE+=	libfaac/faac.pc.in

pre-configure:
	cd ${WRKSRC} && autoreconf -fi

.include "../../mk/bsd.pkg.mk"
