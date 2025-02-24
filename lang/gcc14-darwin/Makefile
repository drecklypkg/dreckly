# $NetBSD$
#
# This gcc14 is specific to Darwin, as upstream does not include support for
# Darwin/aarch64, and it is a large patchset.
#

DISTNAME=	gcc14-14.2.0
CATEGORIES=	lang
MASTER_SITES=	${MASTER_SITE_GITHUB:=iains/}
GITHUB_PROJECT=	gcc-14-branch
GITHUB_TAG=	50f92929f337c81aaf330bb04ac0675dba340e25

MAINTAINER=	jperkin@smartos.org
HOMEPAGE=	https://gcc.gnu.org/
COMMENT=	The GNU Compiler Collection - 14.x Release Series
LICENSE=	gnu-gpl-v2 AND gnu-gpl-v3 AND gnu-lgpl-v2 AND gnu-lgpl-v3

ONLY_FOR_PLATFORM=	Darwin-*-*

USE_LANGUAGES=		c c++
USE_CC_FEATURES=	c99
FORCE_C_STD=		gnu99
USE_CXX_FEATURES=	c++11
FORCE_CXX_STD=		c++11
USE_TOOLS+=		gmake m4 makeinfo perl sed:run tar:build

GNU_CONFIGURE=		yes
GNU_CONFIGURE_STRICT=	no

INFO_FILES=		yes

WRKSRC=			${WRKDIR}/${GITHUB_PROJECT}-${GITHUB_TAG}
OBJDIR=			../build
CONFIGURE_DIRS=		${OBJDIR}
CONFIGURE_SCRIPT=	${WRKSRC}/configure

GCC_PREFIX=		${PREFIX}/${PKGBASE}
GNU_CONFIGURE_PREFIX=	${GCC_PREFIX}

UNLIMIT_RESOURCES+=	datasize stacksize

CHECK_PORTABILITY_SKIP+=	contrib/*
CHECK_PORTABILITY_SKIP+=	gcc/configure.orig_dist

CLEAN_GCC_CFLAGS=	-pipe -g -O2
CONFIGURE_ENV+=		STAGE1_CFLAGS=${CLEAN_GCC_CFLAGS:Q}
CONFIGURE_ENV+=		STAGE1_LDFLAGS=
CONFIGURE_ENV+=		CFLAGS_FOR_TARGET=${CLEAN_GCC_CFLAGS:Q}
CONFIGURE_ENV+=		LDFLAGS_FOR_TARGET=

CONFIGURE_ARGS+=	--disable-bootstrap
CONFIGURE_ARGS+=	--disable-darwin-at-rpath
CONFIGURE_ARGS+=	--disable-libstdcxx-pch
CONFIGURE_ARGS+=	--disable-multilib
CONFIGURE_ARGS+=	--disable-nls
CONFIGURE_ARGS+=	--enable-languages="c,c++,fortran"
CONFIGURE_ARGS+=	--with-boot-ldflags=${BOOT_LDFLAGS:Q}
CONFIGURE_ARGS+=	--with-local-prefix=${GCC_PREFIX:Q}
CONFIGURE_ARGS+=	--with-sysroot=${OSX_SDK_PATH}
CONFIGURE_ARGS+=	--without-zstd

.include "../../mk/bsd.prefs.mk"

.if ${MACHINE_PLATFORM:MDarwin-[0-8].*-*}
CONFIGURE_ARGS+=	--with-dwarf2
.endif

# ${WRKSRC}/fixincludes/ looks for sed and compiles the path to sed into
# a binary so we need to make sure we give it the installed sed and not
# the tool wrapped one.
MAKE_ENV+=		ac_cv_path_SED=${TOOLS_SED}
MAKE_ENV+=		lt_cv_path_SED=${TOOLS_SED}

pre-configure:
	${RUN} cd ${WRKSRC} && ${MKDIR} ${OBJDIR}

CTF_FILES_SKIP+=	*/gengtype	# CPU limit exceeded

TEST_TARGET=	-j ${MAKE_JOBS} -k check || ${TRUE}
TEST_DEPENDS+=	dejagnu-[0-9]*:../../devel/dejagnu

post-test:
	${RUN} cd ${WRKSRC} && cd ${OBJDIR} &&		\
	${SHELL} ${WRKSRC}/contrib/test_summary >${WRKDIR}/test_summary.log
	${INFO_MSG} "Test summary are available in ${WRKDIR}/test_summary.log"

post-install:
	${TEST} -f ${DESTDIR}${GCC_PREFIX}/bin/cc || \
		( cd ${DESTDIR}${GCC_PREFIX}/bin ; ${LN} -f gcc cc )

GENERATE_PLIST+= \
	cd ${DESTDIR}${PREFIX} && \
	    ${FIND} gcc14 \( -type f -o -type l \) -print | ${SORT};

.include "../../devel/gmp/inplace.mk"
.include "../../math/mpcomplex/inplace.mk"
.include "../../math/mpfr/inplace.mk"
.include "../../mk/dlopen.buildlink3.mk"
.include "../../mk/pthread.buildlink3.mk"
.include "../../mk/bsd.pkg.mk"
