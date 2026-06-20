# $NetBSD: Makefile,v 1.19 2015/07/04 16:18:40 joerg Exp $
#

DISTNAME=	dclock
PKGNAME=	dclock-4
PKGREVISION=	1
CATEGORIES=	x11 time
MASTER_SITES=	${MASTER_SITE_XCONTRIB:S/contrib/R5contrib/}
EXTRACT_SUFX=	.shar.Z

MAINTAINER=	pkgsrc-users@NetBSD.org
COMMENT=	Digital clock for X

CONFLICTS+=	ivtools-*

WRKSRC=		${WRKDIR}

# This is old code and it uses patterns (implicit int, K&R style
# function declarations) that predate the original C standard.
#
# To keep it working in the face of a changing C standard,
# force the use of a "known good" version, in this case, the
# minimum bootstrap requirement and not strict standards mode
# so that all APIs remain visible.
FORCE_C_STD=	gnu99

INSTALLATION_DIRS=	bin ${PKGMANDIR}/man1

.include "../../x11/libXt/buildlink3.mk"
.include "../../mk/bsd.pkg.mk"
