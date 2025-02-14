# $NetBSD: options.mk,v 1.1 2024/01/21 08:22:02 taca Exp $

PKG_OPTIONS_VAR=	PKG_OPTIONS.ruby
PKG_SUPPORTED_OPTIONS=	ruby-build-ri-db
PKG_SUGGESTED_OPTIONS=	ruby-build-ri-db

PKG_OPTIONS_OPTIONAL_GROUPS=	jit
PKG_OPTIONS_GROUP.jit=		ruby-rjit ruby-yjit

JIT_PLATFORMS=  aarch64 aarch64eb x86_64

.include "../../lang/rust/platform.mk"

.if ${PLATFORM_SUPPORTS_RUST:tl} == "yes" && ${JIT_PLATFORMS:M${MACHINE_ARCH}}
PKG_SUGGESTED_OPTIONS+=	ruby-yjit
.endif

.include "../../mk/bsd.options.mk"

.if ${PKG_OPTIONS:Mruby-yjit}
CONFIGURE_ARGS+=	--disable-rjit --enable-yjit
RUST_REQ=		1.58.0
.include "../../lang/rust/rust.mk"
.else
CONFIGURE_ENV+=		RUSTC=no
.endif

.if ${PKG_OPTIONS:Mruby-rjit}
CONFIGURE_ARGS+=	--enable-rjit --disable-yjit
.endif

.if ${PKG_OPTIONS:Mruby-build-ri-db}
RUBY_DYNAMIC_DIRS+=	${RUBY_SYSRIDIR}
# Use huge memory.
UNLIMIT_RESOURCES+=	datasize
.else
CONFIGURE_ARGS+=	--enable-install-doc=no
.endif
