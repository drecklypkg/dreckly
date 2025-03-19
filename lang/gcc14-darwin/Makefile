# $NetBSD$
#
# This is a GCC 14.x package specific to Darwin, using the iains branch.
#

DISTNAME=	gcc14-14.2.0
CATEGORIES=	lang
MASTER_SITES=	${MASTER_SITE_GITHUB:=iains/}
GITHUB_PROJECT=	gcc-14-branch
GITHUB_TAG=	50f92929f337c81aaf330bb04ac0675dba340e25

MAINTAINER=	jperkin@pkgsrc.org
HOMEPAGE=	https://gcc.gnu.org/
COMMENT=	The GNU Compiler Collection - Darwin 14.x
LICENSE=	gnu-gpl-v2 AND gnu-gpl-v3 AND gnu-lgpl-v2 AND gnu-lgpl-v3

ONLY_FOR_PLATFORM=	Darwin-*

USE_LANGUAGES=		c c++
USE_CC_FEATURES=	c99
USE_CXX_FEATURES=	c++11

USE_TOOLS+=	flex gmake m4 makeinfo perl sed:run tar:build

GNU_CONFIGURE=		yes
GNU_CONFIGURE_STRICT=	no

# Perform the build outside of ${WRKSRC}
#
WRKSRC=			${WRKDIR}/${GITHUB_PROJECT}-${GITHUB_TAG}
OBJDIR=			../build
CONFIGURE_DIRS=		${OBJDIR}
CONFIGURE_SCRIPT=	../${GITHUB_PROJECT}-${GITHUB_TAG}/configure

GCC_PREFIX=		${PREFIX}/${PKGBASE}
GNU_CONFIGURE_PREFIX=	${GCC_PREFIX}

SUBST_CLASSES+=		vars
SUBST_STAGE.vars=	pre-configure
SUBST_FILES.vars=	gcc/Makefile.in
SUBST_VARS.vars=	MACHINE_GNU_PLATFORM

# Try to ensure a clean build where possible, unaffected by our general
# compiler flags.
#
CLEAN_GCC_CFLAGS=	-pipe -g -O2
CONFIGURE_ENV+=		STAGE1_CFLAGS=${CLEAN_GCC_CFLAGS:Q}
CONFIGURE_ENV+=		STAGE1_LDFLAGS=
CONFIGURE_ENV+=		CFLAGS_FOR_TARGET=${CLEAN_GCC_CFLAGS:Q}
CONFIGURE_ENV+=		LDFLAGS_FOR_TARGET=

CONFIGURE_ARGS+=	--enable-languages="c,c++,fortran,objc,lto"
CONFIGURE_ARGS+=	--disable-bootstrap
CONFIGURE_ARGS+=	--disable-darwin-at-rpath
CONFIGURE_ARGS+=	--disable-multilib
CONFIGURE_ARGS+=	--disable-nls
CONFIGURE_ARGS+=	--with-local-prefix=${GCC_PREFIX:Q}
CONFIGURE_ARGS+=	--with-sysroot=${OSX_SDK_PATH}
CONFIGURE_ARGS+=	--with-zstd=no
CONFIGURE_ARGS+=	--without-system-zlib

UNLIMIT_RESOURCES+=	datasize
UNLIMIT_RESOURCES+=	stacksize

FILES_SUBST+=		MACHINE_GNU_PLATFORM=${MACHINE_GNU_PLATFORM}

CHECK_PORTABILITY_SKIP+=	contrib/*
CHECK_SSP_SUPPORTED=		no		# Clean CFLAGS removes -fstack*
CTF_FILES_SKIP+=		*/gengtype	# Causes ctfconvert to hang

INFO_FILES=		yes

pre-configure:
	${RUN} cd ${WRKSRC} && ${MKDIR} ${OBJDIR}

# There is no reasonable possibility of static PLISTs as the contents differ
# hugely between OS versions (e.g. include-fixed).
#
GENERATE_PLIST+= \
	cd ${DESTDIR}${PREFIX} && \
	    ${FIND} ${PKGBASE} \( -type f -o -type l \) -print | ${SORT};

TEST_TARGET=	-j ${MAKE_JOBS} -k check
TEST_DEPENDS+=	dejagnu-[0-9]*:../../devel/dejagnu

post-test:
	${RUN} cd ${WRKSRC} && cd ${OBJDIR} &&		\
	${SHELL} ${WRKSRC}/contrib/test_summary >${WRKDIR}/test_summary.log
	${INFO_MSG} "Test summary are available in ${WRKDIR}/test_summary.log"

post-install:
	${TEST} -f ${DESTDIR}${GCC_PREFIX}/bin/cc || \
		( cd ${DESTDIR}${GCC_PREFIX}/bin ; ${LN} -f gcc cc )

.include "../../devel/gmp/inplace.mk"
.include "../../math/mpcomplex/inplace.mk"
.include "../../math/mpfr/inplace.mk"
.include "../../mk/dlopen.buildlink3.mk"
.include "../../mk/pthread.buildlink3.mk"
.include "../../mk/bsd.pkg.mk"
