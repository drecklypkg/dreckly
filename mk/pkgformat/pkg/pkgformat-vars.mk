# $NetBSD: pkgformat-vars.mk,v 1.17 2024/04/12 19:56:23 riastradh Exp $
#
# This Makefile fragment is included indirectly by bsd.prefs.mk and
# defines some variables which must be defined earlier than where
# pkgformat.mk is included.
#

PKGSRC_MESSAGE_RECIPIENTS?=	# empty

.if !empty(PKGSRC_MESSAGE_RECIPIENTS)
USE_TOOLS+=	mail
.endif

.if defined(PKG_PRESERVE)
USE_TOOLS+=	date
.endif

# This is the package database directory for the default view.
PKG_DBDIR?=		${LOCALBASE}/pkgdb

# _PKG_DBDIR is the actual packages database directory where we register
# packages.
#
_PKG_DBDIR=		${PKG_DBDIR}

PKG_ADD_CMD?=		${PKG_TOOLS_BIN}/pkg_add
PKG_ADMIN_CMD?=		${PKG_TOOLS_BIN}/pkg_admin
PKG_CREATE_CMD?=	${PKG_TOOLS_BIN}/pkg_create
PKG_DELETE_CMD?=	${PKG_TOOLS_BIN}/pkg_delete
PKG_INFO_CMD?=		${PKG_TOOLS_BIN}/pkg_info

NATIVE_PKG_TOOLS_BIN?=		${PKG_TOOLS_BIN}
NATIVE_PKG_ADD_CMD?=		${NATIVE_PKG_TOOLS_BIN}/pkg_add
NATIVE_PKG_ADMIN_CMD?=		${NATIVE_PKG_TOOLS_BIN}/pkg_admin
NATIVE_PKG_CREATE_CMD?=		${NATIVE_PKG_TOOLS_BIN}/pkg_create
NATIVE_PKG_DELETE_CMD?=		${NATIVE_PKG_TOOLS_BIN}/pkg_delete
NATIVE_PKG_INFO_CMD?=		${NATIVE_PKG_TOOLS_BIN}/pkg_info

# Latest versions of tools required for correct pkgsrc operation.
.if ${USE_PKG_ADMIN_DIGEST:U:tl} == "yes"
PKGTOOLS_REQD=		20191008
.else
PKGTOOLS_REQD=		20100914
.endif
# Latest version of pkg_install required to extract packages
PKGTOOLS_VERSION_REQD=	20091115

# Environment used when invoking package tools.  This is used to pass
# environment variables to the package install and deinstall scripts.
#
PKGTOOLS_ENV?=		# empty

.if !defined(PKGTOOLS_VERSION)
PKGTOOLS_VERSION!=	${NATIVE_PKG_INFO_CMD} -V 2>/dev/null || echo 20010302
MAKEFLAGS+=		PKGTOOLS_VERSION=${PKGTOOLS_VERSION}
.endif

# Check that we are using up-to-date pkg_* tools with this file.
.if !defined(NO_PKGTOOLS_REQD_CHECK) && ${PKGTOOLS_VERSION} < ${PKGTOOLS_REQD}
BOOTSTRAP_DEPENDS+=	pkg_install>=${PKGTOOLS_REQD}:../../pkgtools/pkg_install
_PKG_INSTALL_DEPENDS=	yes
.endif

AUDIT_PACKAGES?=	${PKG_ADMIN}
_AUDIT_PACKAGES_CMD?=	audit-pkg
_EXTRACT_PKGVULNDIR=	${PKG_ADMIN} config-var PKGVULNDIR
DOWNLOAD_VULN_LIST?=	${PKG_ADMIN} fetch-pkg-vulnerabilities
_AUDIT_CONFIG_FILE=	pkg_install.conf
_AUDIT_CONFIG_OPTION=	IGNORE_URL

# The binary pkg_install tools all need to consistently to refer to the
# correct package database directory.
#
PKGTOOLS_ARGS?=		-K ${_PKG_DBDIR}

PKG_ADD?=	${NATIVE_PKG_ADD_CMD} ${PKGTOOLS_ARGS}
PKG_ADMIN?=	${NATIVE_PKG_ADMIN_CMD} ${PKGTOOLS_ARGS}
PKG_CREATE?=	${NATIVE_PKG_CREATE_CMD} ${PKGTOOLS_ARGS}
PKG_DELETE?=	${NATIVE_PKG_DELETE_CMD} ${PKGTOOLS_ARGS}
PKG_INFO?=	${NATIVE_PKG_INFO_CMD} ${PKGTOOLS_ARGS}
