#
# Compiler definitions for GNU Fortran.
#
# User-settable variables:
#
# GFORTRAN_REQD
# 	The major version of GNU Fortran that should be considered for use
# 	on this platform.  This does not guarantee that the version will be
# 	selected, as there may be additional requirements defined in this
# 	file, e.g. to work around known bugs or missing support.
#
# If GFORTRAN_REQD is not defined by the user, then we select an appropriate
# version to use for the target platform.
#

.if !defined(COMPILER_GFORTRAN_MK)
COMPILER_GFORTRAN_MK:=

# Define a default version that should be used unless a more suitable
# candidate is chosen.  Naturally this should have the widest possible
# platform support.
#
GFORTRAN_DEFAULT=	10

.include "../../mk/bsd.prefs.mk"

# If the primary compiler is GCC then add it as the base version to match,
# to avoid unnecessarily building other versions.
#
.if ${PKGSRC_COMPILER:Mgcc}
GFORTRAN_REQD+=	${CC_VERSION:S/gcc-//:R:R}
.endif

# Upstream GCC through at least 14.x does not support Darwin/aarch64.  For
# this platform we have a custom lang/gcc14-darwin build which is handled
# later in this file.
#
.if ${OPSYS} == "Darwin"
GFORTRAN_REQD+=		14
GFORTRAN_PKGPATH.14=	lang/gcc14-darwin
.endif

# Upstream GCC through at least 9.x does not support these NetBSD ports.
#
.if ${MACHINE_PLATFORM:MNetBSD-*-aarch64*} \
 || ${MACHINE_PLATFORM:MNetBSD-*-earm*}
GFORTRAN_REQD+=		10
.endif

# Distill GFORTRAN_REQD down to a single _GFORTRAN_REQD variable that is
# set to the highest version required.  If at the end of the selection it
# is still set to 0, then choose an appropriate default.
#
.if !defined(_GFORTRAN_REQD)
_GFORTRAN_REQD=		0
.  for _v_ in ${GFORTRAN_REQD}
_REQD_IS_HIGHER!=							\
	${PKG_ADMIN} pmatch 't>=${_GFORTRAN_REQD}' t-${_v_} 2>/dev/null	\
		&& ${ECHO} yes || ${ECHO} no
.    if ${_REQD_IS_HIGHER} == "yes"
_GFORTRAN_REQD=	${_v_}
.    endif
.  endfor
.  if ${_GFORTRAN_REQD} == 0
_GFORTRAN_REQD=	${GFORTRAN_DEFAULT}
.  endif
.endif

# Define paths mapping _GFORTRAN_REQD to available GCC packages.  For some
# systems we have a separate GCC package due to missing upstream support, in
# which case we set an override first before the default value is selected.
#
.for _v_ in 6 7 8 9 10 12 13 14
GFORTRAN_PKGPATH.${_v_}:=	${GFORTRAN_PKGPATH.${_v_}:Ulang/gcc${_v_}}
.endfor
GFORTRAN_PKGPATH:=		${GFORTRAN_PKGPATH.${_GFORTRAN_REQD}}

# If USE_LANGUAGES specifies a matching fortran then enable.
#
_USE_GFORTRAN=		no
LANGUAGES.gfortran=	fortran fortran77
.for _lang_ in ${USE_LANGUAGES}
.  if ${LANGUAGES.gfortran:M${_lang_}}
_USE_GFORTRAN=		yes
.  endif
.endfor

.if ${_USE_GFORTRAN} == yes
_GFORTRANBASE=		${TOOLBASE}/gcc${_GFORTRAN_REQD}
_GFORTRAN_DIR=		${WRKDIR}/.gfortran
FC=			gfortran
PKG_FC?=		${FC}
_GFORTRAN_FC:=		${_GFORTRAN_DIR}/bin/${PKG_FC:T}
_ALIASES.FC+=		f77 g77 g95 gfortran
FCPATH=			${_GFORTRANBASE}/bin/gfortran
PKG_FC:=		${_GFORTRAN_FC}
PREPEND_PATH+=		${_GFORTRAN_DIR}/bin

# For now we add a full dependency on the GCC package.  At some point this
# really needs to be enhanced to support the -libs packages.
#
BUILDLINK_DEPMETHOD.gcc${_GFORTRAN_REQD}=	full
.include "../../${GFORTRAN_PKGPATH}/buildlink3.mk"

# Create symlinks for the compiler into ${WRKDIR}.
.  if !target(${_GFORTRAN_FC})
override-tools: ${_GFORTRAN_FC}
${_GFORTRAN_FC}:
	${RUN}${MKDIR} ${.TARGET:H};					\
	${LN} -fs ${_GFORTRANBASE}/bin/gfortran ${.TARGET}
.    for _alias_ in ${_ALIASES.FC:S/^/${.TARGET:H}\//}
	${RUN}								\
	if [ ! -x "${_alias_}" ]; then					\
		${LN} -fs ${_GFORTRANBASE}/bin/gfortran ${_alias_};	\
	fi
.    endfor
.  endif
.endif

.endif
