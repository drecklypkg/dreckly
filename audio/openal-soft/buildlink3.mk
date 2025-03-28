# $NetBSD: buildlink3.mk,v 1.1 2016/02/08 01:53:48 markd Exp $

BUILDLINK_TREE+=	openal-soft

.include "../../mk/compiler.mk"

# Use the C version of OpenAL with older GCC versions and
# compilers other than GCC/Clang.  This test is likely incomplete.
.if (!${PKGSRC_COMPILER:M*gcc*} && ${COMPILER_VERSION} < 100000) || \
    (!${PKGSRC_COMPILER:M*gcc*} && !${PKGSRC_COMPILER:M*clang*})
OPENAL_USE_CXX?=	no
.else
OPENAL_USE_CXX?=	yes
.endif

.if ${OPENAL_USE_CXX:tl} == "no"
.  include "../../audio/openal-soft-c/buildlink3.mk"
.endif

.if !defined(OPENAL_SOFT_BUILDLINK3_MK)
OPENAL_SOFT_BUILDLINK3_MK:=

BUILDLINK_API_DEPENDS.openal-soft+=	openal-soft>=1.5.304
BUILDLINK_PKGSRCDIR.openal-soft?=	../../audio/openal-soft
.endif	# OPENAL_SOFT_BUILDLINK3_MK

BUILDLINK_TREE+=	-openal-soft
