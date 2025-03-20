# $NetBSD: buildlink3.mk,v 1.1 2024/06/28 18:35:17 wiz Exp $

BUILDLINK_TREE+=	gcc14-libs

.if !defined(GCC14_LIBS_BUILDLINK3_MK)
GCC14_LIBS_BUILDLINK3_MK:=

BUILDLINK_API_DEPENDS.gcc14-libs+=	gcc14-libs>=0
BUILDLINK_PKGSRCDIR.gcc14-libs=		../../lang/gcc14-libs
BUILDLINK_DEPMETHOD.gcc14-libs?=	full

BUILDLINK_PASSTHRU_DIRS+=	${BUILDLINK_PREFIX.gcc14-libs}/gcc14
BUILDLINK_FILES.gcc14-libs=	# empty
BUILDLINK_AUTO_VARS.gcc14-libs=	no

# Use custom specs file to ensure we link against the GCC libraries from
# this package.  Some OPSYS also have additional handling so support custom
# source files.
#
OPSYSVARS+=		SPECS_SRC
SPECS_SRC.SunOS=	${BUILDLINK_PKGSRCDIR.gcc14-libs}/files/specs.illumos
SPECS_SRC.*=		${BUILDLINK_PKGSRCDIR.gcc14-libs}/files/specs

SPECS_LIBGCC=		${WRAPPER_DIR}/specs.libgcc
WRAPPER_TARGETS+=	${SPECS_LIBGCC}

LIBGCC_PREFIX=	${BUILDLINK_PREFIX.gcc14-libs}/gcc14/${MACHINE_GNU_PLATFORM}

SPECS_SED=	-e '/^\#/d'
SPECS_SED+=	-e 's,@LINKER_RPATH_FLAG@,${LINKER_RPATH_FLAG},g'
SPECS_SED+=	-e 's,@LIBGCC_PREFIX@,${PREFIX}${LIBGCC_PREFIX},g'

.include "../../mk/bsd.fast.prefs.mk"

# The specs file for illumos additionally has some sanitisation of the default
# library search path.
.if ${MACHINE_PLATFORM:MSunOS-*-x86_64}
SPECS_SED+=	-e 's,@LINK_ARCH_DEFAULT@,link_arch64,g'
SPECS_SED+=	-e 's,@LINK_LIBGCC_DEFAULT@,link_libgcc_arch64,g'
.elif ${MACHINE_PLATFORM:MSunOS-*-i386}
SPECS_SED+=	-e 's,@LINK_ARCH_DEFAULT@,link_arch32,g'
SPECS_SED+=	-e 's,@LINK_LIBGCC_DEFAULT@,link_libgcc_arch32,g'
.endif

${SPECS_LIBGCC}:
	${SED} ${SPECS_SED} < ${SPECS_SRC} > ${SPECS_LIBGCC}

_WRAP_EXTRA_ARGS.CC+=	-specs=${SPECS_LIBGCC}
_WRAP_EXTRA_ARGS.CXX+=	-specs=${SPECS_LIBGCC}
_WRAP_EXTRA_ARGS.FC+=	-specs=${SPECS_LIBGCC}
CWRAPPERS_APPEND.cc+=	-specs=${SPECS_LIBGCC}
CWRAPPERS_APPEND.cxx+=	-specs=${SPECS_LIBGCC}
CWRAPPERS_APPEND.f77+=	-specs=${SPECS_LIBGCC}

.include "../../mk/dlopen.buildlink3.mk"
.include "../../mk/pthread.buildlink3.mk"
.endif

BUILDLINK_TREE+=	-gcc14-libs
