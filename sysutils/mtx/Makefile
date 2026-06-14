# $NetBSD: Makefile,v 1.3 2017/09/03 08:37:00 wiz Exp $

DISTNAME=	mtx-1.3.12
PKGREVISION=	1
CATEGORIES=	sysutils
MASTER_SITES=	${MASTER_SITE_SOURCEFORGE:=mtx/mtx-stable/1.3.12/}

MAINTAINER=	bouyer@NetBSD.org
#HOMEPAGE=	http://mtx.badtux.net/
COMMENT=	Control SCSI media changer devices
LICENSE=	gnu-gpl-v2

USE_TOOLS+=	gmake 
GNU_CONFIGURE=	yes

# Defines its own boolean type which conflicts with C23 types.
FORCE_C_STD=	gnu89

.include "../../mk/bsd.pkg.mk"
