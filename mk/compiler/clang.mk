# $NetBSD: clang.mk,v 1.45 2024/03/27 11:33:00 schmonz Exp $
#
# This is the compiler definition for the clang compiler.
#
# User-settable variables:
#
# CLANGBASE
#	The base directory where the compiler is installed.
#

.if !defined(COMPILER_CLANG_MK)
COMPILER_CLANG_MK=	defined

# Add the dependency on clang
# TODO: may be installed already, check for this
#TOOL_DEPENDS+= clang-[0-9]*:../../lang/clang

.include "../../mk/bsd.prefs.mk"

CLANGBASE?=		${TOOLBASE}
LANGUAGES.clang=	# empty

.if exists(${CLANGBASE}/bin/clang)
LANGUAGES.clang+=	c objc
_COMPILER_STRIP_VARS+=	CC
CCPATH=			${CLANGBASE}/bin/clang
PKG_CC:=		${CCPATH}
.endif

.if exists(${CLANGBASE}/bin/clang++)
LANGUAGES.clang+=	c++
_COMPILER_STRIP_VARS+=	CXX
CXXPATH=		${CLANGBASE}/bin/clang++
PKG_CXX:=		${CXXPATH}
.endif

.if exists(${CLANGBASE}/bin/clang-cpp)
CPPPATH=		${CLANGBASE}/bin/clang-cpp
PKG_CPP:=		${CPPPATH}
.endif

.if !defined(CC_VERSION)
.  if exists(${CCPATH})
CLANG_VERSION!=		${CCPATH} -dumpversion 2>&1 || ${ECHO} 0
.  else
CLANG_VERSION=		0
.  endif
CC_VERSION=		clang-${CLANG_VERSION}
.endif

# As a user may have preset CC_VERSION we cannot rely on CLANG_VERSION being
# set, so we dig it back out of CC_VERSION.
#
_CLANG_VERSION:=	${CC_VERSION:S/clang-//}

# Calculate _COMPILER_VERSION.  Abuse bmake's localtime support to convert to
# %02d without having to fork.  This is limited to a maximum of 59, but that
# should be more than enough to last for a while at the current clang release
# cadence.
#
# This gets turned into COMPILER_VERSION by compiler.mk.
#
.if ${_CLANG_VERSION:M*.*.*.*}
_CC_MAJOR=	${_CLANG_VERSION:R:R:R}
_CC_MINOR=	${_CLANG_VERSION:R:R:E}
_CC_PATCH=	${_CLANG_VERSION:R:E}
.elif ${_CLANG_VERSION:M*.*.*}
_CC_MAJOR=	${_CLANG_VERSION:R:R}
_CC_MINOR=	${_CLANG_VERSION:R:E}
_CC_PATCH=	${_CLANG_VERSION:E}
.elif ${_CLANG_VERSION:M*.*}
_CC_MAJOR=	${_CLANG_VERSION:R}
_CC_MINOR=	${_CLANG_VERSION:E}
_CC_PATCH=	0
.else
_CC_MAJOR=	${_CLANG_VERSION}
_CC_MINOR=	0
_CC_PATCH=	0
.endif

_FMT=		%S
_CC_MAJOR:=	${${_CC_MAJOR} == "0":?00:${_FMT:localtime=${_CC_MAJOR}}}
_CC_MINOR:=	${${_CC_MINOR} == "0":?00:${_FMT:localtime=${_CC_MINOR}}}
_CC_PATCH:=	${${_CC_PATCH} == "0":?00:${_FMT:localtime=${_CC_PATCH}}}

_COMPILER_VERSION:=	${_CC_MAJOR}${_CC_MINOR}${_CC_PATCH}

_COMPILER_ABI_FLAG.32=	-m32
_COMPILER_ABI_FLAG.64=	-m64

.include "gcc-style-args.mk"

LDFLAGS+=	${_CLANG_LDFLAGS}

# _LANGUAGES.<compiler> is ${LANGUAGES.<compiler>} restricted to the
# ones requested by the package in USE_LANGUAGES.
#
_LANGUAGES.clang=	# empty
.for _lang_ in ${USE_LANGUAGES}
_LANGUAGES.clang+=	${LANGUAGES.clang:M${_lang_}}
.endfor

PKGSRC_FORTRAN?=gfortran

.if !empty(PKGSRC_FORTRAN) && (!empty(USE_LANGUAGES:Mfortran) || !empty(USE_LANGUAGES:Mfortran77))
.  include "../../mk/compiler/${PKGSRC_FORTRAN}.mk"
.endif

_WRAP_EXTRA_ARGS.CC+=	-Qunused-arguments
CWRAPPERS_APPEND.cc+=	-Qunused-arguments
CWRAPPERS_PREPEND.cc+=	-Qunused-arguments
_WRAP_EXTRA_ARGS.CXX+=	-Qunused-arguments
CWRAPPERS_APPEND.cxx+=	-Qunused-arguments

.if defined(_PKGSRC_BARRIER)
# Xcode 12 (Apple clang-1200.0.32.2) and upstream Clang 16 have a
# zealous new default that the wide world of random third-party software
# isn't ready for. Turn it back off by default.
#
# Packages and users can override via CFLAGS/CPPFLAGS.
_NOERROR_IMPLICIT_cmd=	${CCPATH} -\#\#\# -E -x c /dev/null \
			2>&1 \
			| ${GREP} -q Werror=implicit-function-declaration \
			&& ${ECHO} -Wno-error=implicit-function-declaration \
			|| ${TRUE}
CWRAPPERS_PREPEND.cc+=	${_NOERROR_IMPLICIT_cmd:sh}

# Xcode 15 (Apple clang-1500.3.9.4) and upstream Clang 16 have several
# more zealous new defaults. We can't default them off as precisely
# (they don't show up in `clang -###` output), so we simply attempt to
# turn them off for any clang that doesn't complain when we try.
#
# Packages and users can override via CFLAGS/CPPFLAGS.
#
# As soon as 2024Q1 branches, we should:
#
# 1. Do a bulk build with all these -Wno-error tweaks removed, so we can
#    see how much is broken.
# 2. If it's "too much" breakage and we'll have to keep overriding these
#    compiler defaults for "a while", find a way to accomplish them with
#    fewer compiler invocations. (Some ideas: define a default
#    FORCE_C_STD, or apply overrides keyed on CC_VERSION or similar.) Do
#    a bulk build to make sure things continue to work as before.
# 3. Otherwise, fix as much as we can before 2024Q2. This will help with
#    gcc 14 (which has many similar new defaults) as well.
_WERROR_CLANG16=	implicit-int int-conversion incompatible-pointer-types
_NOERROR_CLANG16_cmd=	for _warn_ in ${_WERROR_CLANG16}; do \
			${CCPATH} -\#\#\# -Wno-error=$${_warn_} -x c /dev/null \
			>/dev/null 2>&1 \
			&& ${ECHO} -Wno-error=$${_warn_} \
			|| ${TRUE}; \
			done
CWRAPPERS_PREPEND.cc+=	${_NOERROR_CLANG16_cmd:sh}
.endif

.for _version_ in ${_CXX_STD_VERSIONS}
_CXX_STD_FLAG.${_version_}?=	-std=${_version_}
.endfor

.endif	# COMPILER_CLANG_MK
