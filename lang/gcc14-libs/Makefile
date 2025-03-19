# $NetBSD: Makefile,v 1.3 2025/01/07 19:56:45 riastradh Exp $

PKGNAME=	gcc14-libs-1.0
CATEGORIES=	lang
MASTER_SITES=	# empty
DISTFILES=	# empty

MAINTAINER=	pkgsrc-users@NetBSD.org
HOMEPAGE=	https://gcc.gnu.org/
COMMENT=	The GNU Compiler Collection (GCC) support shared libraries
LICENSE=	gnu-gpl-v2 AND gnu-gpl-v3 AND gnu-lgpl-v2 AND gnu-lgpl-v3

USE_TOOLS+=	pax

NO_BUILD=		yes
CHECK_SHLIBS=		no
CHECK_SSP_SUPPORTED=	no
RELRO_SUPPORTED=	no

OPSYSVARS+=		GCC14DIR
GCC14DIR.Darwin=	lang/gcc14-darwin
GCC14DIR.SunOS=		lang/gcc14-illumos
GCC14DIR.*=		lang/gcc14

BUILD_DEPENDS+=		gcc14-[0-9]*:../../${GCC14DIR}

LIBRARY_FILES=		${WRKDIR}/lib_files
INSTALLATION_DIRS+=	gcc14/${MACHINE_GNU_PLATFORM}
GENERATE_PLIST+=	${SED} -e 's,^,gcc14/${MACHINE_GNU_PLATFORM}/,'	\
				${LIBRARY_FILES};

.include "../../mk/bsd.prefs.mk"

# On SunOS with multilib support we want to exclude the non-default arch, i.e.
# prune 32-bit libraries from the 64-bit package and vice versa.  Also fix the
# library paths so that CHECK_SHLIBS is clean.
#
.if ${MACHINE_PLATFORM:MSunOS-*-x86_64}
LIBPATH=	gcc14/${MACHINE_GNU_PLATFORM}/lib/amd64
SKIP_LIBS=	-e '/lib\/lib/d'
.elif ${MACHINE_PLATFORM:MSunOS-*-i386}
LIBPATH=	gcc14/${MACHINE_GNU_PLATFORM}/lib
SKIP_LIBS=	-e '/lib\/amd64/d'
.endif

# Only include libraries that packages depend upon via REQUIRES.
${LIBRARY_FILES}:
	${RUN} ${PKG_INFO} -qL gcc14 | ${SED} -n			\
	    -e 's,^${PREFIX}/gcc14/,,'					\
	    ${SKIP_LIBS}						\
	    -e '/gdb.py/d'						\
	    -e '/lib\/lib.*\.${SHLIB_EXT}/p'				\
		> ${LIBRARY_FILES}

do-install: ${LIBRARY_FILES}
	${RUN} cd ${PREFIX}/gcc14 && ${PAX}				\
	    -rw ${DESTDIR}${PREFIX}/gcc14/${MACHINE_GNU_PLATFORM}	\
		< ${LIBRARY_FILES}
.if ${OPSYS} == "SunOS"
	${RUN} for f in ${DESTDIR}${PREFIX}/${LIBPATH}/*.so; do		\
		${ELFEDIT} -e 'dyn:runpath ${PREFIX}/${LIBPATH}' $$f;	\
	done
.endif

.include "../../mk/dlopen.buildlink3.mk"
.include "../../mk/pthread.buildlink3.mk"
.include "../../mk/bsd.pkg.mk"
