# $NetBSD: buildlink3.mk,v 1.9 2009/03/20 19:25:09 joerg Exp $

BUILDLINK_TREE+=	libares

.if !defined(LIBARES_BUILDLINK3_MK)
LIBARES_BUILDLINK3_MK:=

.include "../../mk/bsd.fast.prefs.mk"

BUILDLINK_API_DEPENDS.libares+=	libares>=1.1.1
BUILDLINK_PKGSRCDIR.libares?=	../../net/libares
BUILDLINK_DEPMETHOD.libares?=	build

.endif # LIBARES_BUILDLINK3_MK

BUILDLINK_TREE+=	-libares
