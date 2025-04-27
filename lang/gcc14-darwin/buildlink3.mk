# $NetBSD$

BUILDLINK_TREE+=	gcc14

.if !defined(GCC14_BUILDLINK3_MK)
GCC14_BUILDLINK3_MK:=

BUILDLINK_API_DEPENDS.gcc14+=	gcc14>=14.1.0
BUILDLINK_ABI_DEPENDS.gcc14+=	gcc14>=14.1.0
BUILDLINK_PKGSRCDIR.gcc14=	../../lang/gcc14-darwin
BUILDLINK_DEPMETHOD.gcc14?=	build

BUILDLINK_PASSTHRU_DIRS+=	${BUILDLINK_PREFIX.gcc14}/gcc14

BUILDLINK_FILES.gcc14=		# empty
BUILDLINK_AUTO_VARS.gcc14=	no

pkgbase := gcc14
.include "../../mk/pkg-build-options.mk"
.include "../../mk/dlopen.buildlink3.mk"
.include "../../mk/pthread.buildlink3.mk"
.endif

BUILDLINK_TREE+=	-gcc14
