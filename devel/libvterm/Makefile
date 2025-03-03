# $NetBSD$

DISTNAME=	libvterm-0.3.3
CATEGORIES=	devel
MASTER_SITES=	https://www.leonerd.org.uk/code/libvterm/

MAINTAINER=	pkgsrc-users@NetBSD.org
HOMEPAGE=	https://www.leonerd.org.uk/code/libvterm/
COMMENT=	Abstract VT220/xterm/ECMA-48 emulation library
LICENSE=	mit

PREV_PKGPATH=	devel/libvterm03
SUPERSEDES+=	libvterm03-[0-9]*

USE_TOOLS+=	gmake perl
USE_LIBTOOL=	yes

MAKE_FLAGS+=		PREFIX=${PREFIX}
PKGCONFIG_OVERRIDE+=	vterm.pc.in
INSTALLATION_DIRS+=	lib/pkgconfig

INSTALL_TARGET=	install-lib install-inc

TEST_TARGET=		test
TEST_ENV.Darwin+=	DYLD_LIBRARY_PATH=${WRKSRC}/.libs

.include "../../mk/bsd.pkg.mk"
