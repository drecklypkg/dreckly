# $NetBSD$

DISTNAME=	tsugaru-20260522
CATEGORIES=	emulators
MASTER_SITES=	${MASTER_SITE_GITHUB:=captainys/}
GITHUB_PROJECT=	TOWNSEMU
GITHUB_TAG=	v${PKGVERSION_NOREV}

# Should use the most recent commit at the time of when a new release is made.
GITHUB_SUBMODULES+=	captainys public 8cabce7e045b23ad68fdb8592aeacd8d9101e362 gui/src/public

MAINTAINER=	pkgsrc-users@NetBSD.org
HOMEPAGE=	http://ysflight.in.coocan.jp/FM/towns/Tsugaru/e.html
COMMENT=	FM Towns emulator
LICENSE=	modified-bsd

CMAKE_CONFIGURE_ARGS=	${WRKSRC}/gui/src

USE_LANGUAGES=	c c++

USE_CXX_FEATURES+=	c++17

CFLAGS.NetBSD+=	-DEBADFD=EBADF
CFLAGS.NetBSD+=	-DESTRPIPE=EPIPE

INSTALLATION_DIRS+=	bin
INSTALLATION_DIRS+=	share/applications
INSTALLATION_DIRS+=	share/pixmaps

pre-build:
	${PREFIX}/bin/icotool -x -i 1 \
		${WRKSRC}/src/resources/tsugaru_icon.ico \
		-o ${WRKDIR}/256.png

do-install:
	${INSTALL_PROGRAM} ${WRKSRC}/${CMAKE_BUILD_DIR}/main_gui/Tsugaru_GUI \
		${DESTDIR}${PREFIX}/bin/${PKGBASE}
	${INSTALL_DATA} ${WRKDIR}/256.png \
		${DESTDIR}${PREFIX}/share/pixmaps/${PKGBASE}.png
	${INSTALL_DATA} ${FILESDIR}/${PKGBASE}.desktop \
		${DESTDIR}${PREFIX}/share/applications

.include "../../devel/cmake/build.mk"
.include "../../audio/alsa-lib/buildlink3.mk"
.include "../../graphics/glu/buildlink3.mk"
.include "../../sysutils/desktop-file-utils/desktopdb.mk"
.include "../../x11/libX11/buildlink3.mk"
.include "../../mk/bsd.pkg.mk"
