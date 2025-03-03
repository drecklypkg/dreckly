# $NetBSD$

BUILDLINK_TREE+=	libvterm

.if !defined(LIBVTERM_BUILDLINK3_MK)
LIBVTERM_BUILDLINK3_MK:=

BUILDLINK_API_DEPENDS.libvterm+=	libvterm>=0.3.3
BUILDLINK_ABI_DEPENDS.libvterm+=	libvterm>=0.3.3
BUILDLINK_PKGSRCDIR.libvterm?=		../../devel/libvterm

.endif	# LIBVTERM_BUILDLINK3_MK

BUILDLINK_TREE+=	-libvterm
