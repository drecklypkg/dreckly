# $NetBSD: Makefile,v 1.8 2024/12/08 16:34:38 vins Exp $

DISTNAME=	emwm-src-1.3
PKGNAME=	${DISTNAME:S,-src,,}
CATEGORIES=	wm
MASTER_SITES=	https://fastestcode.org/dl/
DIST_SUBDIR=	${PKGNAME_NOREV}
EXTRACT_SUFX=	.tar.xz
DISTFILES+=	${DEFAULT_DISTFILES} app-icons.tar.xz	\
		gtk-configs.tar.xz Xresources-sample
SITES.Xresources-sample=	${MASTER_SITES:S/dl/misc/}

MAINTAINER=	vins@NetBSD.org
HOMEPAGE=	https://fastestcode.org/emwm.html
COMMENT=	Enhanced Motif Window Manager
LICENSE=	gnu-lgpl-v2.1 AND cc-by-sa-v3.0

USE_BSD_MAKEFILE=	yes

EGDIR=		share/examples/${PKGBASE}
EGFILES=	gtk-configs/* Xresources-sample

MAKE_FLAGS+=	CC=${CC:Q}
MAKE_FLAGS+=	CFLAGS=${CFLAGS:Q}
MAKE_FLAGS+=	LDFLAGS=${LDFLAGS:Q}
MAKE_FLAGS+=	RCDIR=${PREFIX}/lib/X11

INSTALLATION_DIRS+=	${EGDIR} share/pixmaps
INSTALLATION_DIRS+=	bin
INSTALLATION_DIRS+=	man/man1
INSTALLATION_DIRS+=	man/man4
INSTALLATION_DIRS+=	lib/X11/app-defaults

post-install:
	${INSTALL_DATA} ${EGFILES:S|^|${WRKDIR}/|}	\
		${DESTDIR}${PREFIX}/${EGDIR}
	${INSTALL_DATA} ${WRKDIR}/icons/*.xpm		\
		${DESTDIR}${PREFIX}/share/pixmaps

do-install:
	${INSTALL_PROGRAM} ${WRKSRC}/src/emwm \
		${DESTDIR}${PREFIX}/bin
	${INSTALL_MAN} ${WRKSRC}/src/emwm.1 \
		${DESTDIR}${PREFIX}/${PKGMANDIR}/man1
	${INSTALL_MAN} ${WRKSRC}/src/emwmrc.4 \
		${DESTDIR}${PREFIX}/${PKGMANDIR}/man4
	${INSTALL_DATA} ${WRKSRC}/src/system.emwmrc \
		${DESTDIR}${PREFIX}/lib/X11/system.emwmrc
	${INSTALL_DATA} ${WRKSRC}/src/Emwm.ad \
		${DESTDIR}${PREFIX}/lib/X11/app-defaults/Emwm

.include "../../x11/libXinerama/buildlink3.mk"
.include "../../x11/libXrandr/buildlink3.mk"
.include "../../x11/libXt/buildlink3.mk"
.include "../../mk/motif.buildlink3.mk"
.include "../../mk/bsd.pkg.mk"
