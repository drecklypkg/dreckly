# $NetBSD: Makefile,v 1.225 2024/11/27 07:02:35 adam Exp $

.include "Makefile.common"

COMMENT=	Cross platform make

USE_CURSES=		wsyncup
USE_TOOLS+=		gmake pkg-config
HAS_CONFIGURE=		yes
CONFIGURE_SCRIPT=	bootstrap

BUILD_TARGET=		default_target

CONFIGURE_HAS_MANDIR=	no
CONFIGURE_ARGS+=	--mandir=/${PKGMANDIR}
CONFIGURE_ARGS+=	--docdir=/share/doc/cmake-${CMAKE_API}
CONFIGURE_ARGS+=	--parallel=${MAKE_JOBS:U1}
CONFIGURE_ARGS+=	--prefix=${PREFIX}
CONFIGURE_ARGS+=	--no-system-libs
CONFIGURE_ARGS+=	--no-debugger

LDFLAGS.Darwin+=	-framework CoreServices # for LSOpenCFURLRef()
LDFLAGS.SunOS+=		-lsocket -lnsl

.include "../../mk/bsd.prefs.mk"

.if ${INSTALL_UNSTRIPPED:Uno:tl} != yes
INSTALL_TARGET=		install/strip
.endif

# Enforce arm64 to support building inside x86_64 chroots.
.if ${MACHINE_PLATFORM:MDarwin-*-aarch64}
CONFIGURE_ENV+=		CMAKE_OSX_ARCHITECTURES=arm64
.endif

PRINT_PLIST_AWK+=	{ gsub(/cmake-${CMAKE_API}/, "cmake-$${CMAKE_API}") }
PLIST_SUBST+=		CMAKE_API=${CMAKE_API}

REPLACE_SH=		Modules/Compiler/XL-Fortran/cpp

# for Source/cmDependsJavaParser.cxx
UNLIMIT_RESOURCES=	datasize

# as of 2.4.6, x11 and fortran tests fail in pkgsrc
TEST_TARGET=		test

SUBST_CLASSES+=		cmake
SUBST_STAGE.cmake=	pre-configure
SUBST_MESSAGE.cmake=	Fixing LOCALBASE and X11 paths.
SUBST_FILES.cmake+=	Modules/FindX11.cmake
SUBST_FILES.cmake+=	Modules/Platform/UnixPaths.cmake
SUBST_VARS.cmake=	LOCALBASE X11BASE

# Use custom shell for Makefiles. For most platforms this is a no-op.
# On Darwin, system /bin/sh is restricted, so DYLD_LIBRARY_PATH can't be used.
# This is needed for packages that execute binaries linked with not-yet
# installed shared libraries, like qt6-qtbase.
SUBST_CLASSES+=		shell
SUBST_STAGE.shell=	pre-configure
SUBST_MESSAGE.shell=	Set custom SHELL in generated Makefiles.
SUBST_FILES.shell+=	Source/cmLocalUnixMakefileGenerator3.cxx
SUBST_SED.shell=	-e 's,/bin/sh,${SH},g'

pre-configure:
	${CP} ${FILESDIR}/Source_Checks_cm_cxx_cbegin.cxx ${WRKSRC}/Source/Checks/cm_cxx_cbegin.cxx
	${CP} ${FILESDIR}/Source_Checks_cm_cxx_cend.cxx ${WRKSRC}/Source/Checks/cm_cxx_cend.cxx
	${CP} ${FILESDIR}/Source_Checks_cm_cxx_size_t.cxx ${WRKSRC}/Source/Checks/cm_cxx_size_t.cxx
	${FIND} ${WRKSRC}/Modules -type f -a -name "*.orig" -print | ${XARGS} ${RM}
	${LN} -f ${WRKSRC}/Modules/Platform/OpenBSD.cmake ${WRKSRC}/Modules/Platform/MirBSD.cmake
.for lang in C CXX Fortran
	${LN} -f ${WRKSRC}/Modules/Platform/SunOS-GNU-${lang}.cmake \
	    ${WRKSRC}/Modules/Platform/SunOS-Clang-${lang}.cmake
.endfor

.include "../../mk/atomic64.mk"
.include "../../mk/curses.buildlink3.mk"
.include "../../mk/pthread.buildlink3.mk"
.include "../../mk/bsd.pkg.mk"
