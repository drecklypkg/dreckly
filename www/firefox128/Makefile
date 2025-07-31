# $NetBSD: Makefile,v 1.276 2024/11/17 07:16:50 wiz Exp $

DISTNAME=	firefox-128.8.0esr.source
PKGNAME=	${DISTNAME:S/esr.source$//}
PKGREVISION=	1
CATEGORIES=	www
MASTER_SITES=	${MASTER_SITE_MOZILLA:=firefox/releases/${PKGVERSION_NOREV}esr/source/}
MASTER_SITES+=	${MASTER_SITE_MOZILLA_ALL:=firefox/releases/${PKGVERSION_NOREV}esr/source/}
EXTRACT_SUFX=	.tar.xz

NODEJSKIT=		nodejs-output-128.0.tgz
DISTFILES=		${DEFAULT_DISTFILES} ${NODEJSKIT}
SITES.${NODEJSKIT}=	${MASTER_SITE_LOCAL}

MAINTAINER=	pkgsrc-users@NetBSD.org
HOMEPAGE=	https://www.mozilla.org/en-US/firefox/enterprise/
COMMENT=	Web browser with support for extensions
LICENSE=	mpl-2.0

TOOL_DEPENDS+=	nasm>=2.13:../../devel/nasm

# trademark considerations
APP_NAME=	Iceweasel

WRKSRC=		${WRKDIR}/firefox-${PKGVERSION_NOREV}
PLIST_SRC+=	${PLIST_SRC_DFLT}
USE_LANGUAGES+=	c c++
USE_TOOLS+=	unzip pax tar zip
USE_TOOLS+=	pkg-config perl gmake

OBJDIR=		../build

GCC_REQD+=	8

.include "../../mk/bsd.prefs.mk"

CONFIGURE_ENV+=		CPP=${CPP:Q}
ALL_ENV+=		SHELL=${CONFIG_SHELL:Q}

CONFIGURE_DIRS=		${OBJDIR}
CONFIGURE_SCRIPT=	${WRKSRC}/configure

HAS_CONFIGURE=		yes
CONFIGURE_ARGS+=	--prefix=${PREFIX}
CONFIGURE_ARGS+=	--enable-application=browser
CONFIGURE_ARGS+=	--enable-default-toolkit=cairo-gtk3
CONFIGURE_ARGS+=	--enable-release
CONFIGURE_ARGS+=	--enable-optimize=-O2
CONFIGURE_ARGS+=	--disable-jemalloc
CONFIGURE_ARGS+=	--disable-tests
CONFIGURE_ARGS+=	--with-system-libvpx
CONFIGURE_ARGS+=	--with-system-nspr
CONFIGURE_ARGS+=	--with-system-nss
CONFIGURE_ARGS+=	--with-system-webp
CONFIGURE_ARGS+=	--with-system-zlib
CONFIGURE_ARGS+=	--with-libclang-path=${PREFIX}/lib
CONFIGURE_ARGS+=	--disable-crashreporter
CONFIGURE_ARGS+=	--disable-debug
CONFIGURE_ARGS+=	--disable-icf
CONFIGURE_ARGS+=	--disable-rust-simd
CONFIGURE_ARGS+=	--disable-updater
CONFIGURE_ARGS+=	--enable-chrome-format=omni
CONFIGURE_ARGS+=	--enable-update-channel=esr
CONFIGURE_ARGS+=	--enable-system-ffi

UNLIMIT_RESOURCES+=	datasize virtualsize

ALL_ENV+=		MOZILLA_PKG_NAME=${PKGBASE}

LDFLAGS+=		${COMPILER_RPATH_FLAG}${PREFIX}/lib/${PKGBASE}

.include "../../mk/compiler.mk"

.if empty(PKGSRC_COMPILER:Mclang)
# Set path to "clang for cbindgen" when target compiler is not clang.
CONFIGURE_ARGS+=	--with-clang-path=${PREFIX}/bin/clang
.endif

# ERROR: Unsupported linker bfd
CONFIGURE_ARGS.Darwin+=	--enable-linker=ld64

PYTHON_VERSIONS_ACCEPTED=	310 39
PYTHON_FOR_BUILD_ONLY=		tool

.include "../../lang/python/batteries-included.mk"
.include "../../lang/python/tool.mk"

TOOL_DEPENDS+=		cbindgen>=0.24.3:../../devel/cbindgen

.if ${MACHINE_ARCH} == "i386" || ${MACHINE_ARCH} == "x86_64"
TOOL_DEPENDS+=		yasm>=1.1:../../devel/yasm
.endif

# This is to work around build failures where an upstream configuration script
# is confused by having more than one approximate match to MACHINE_GNU_PLATFORM
# "i486" when attempting to select the Rust compiler target.
.if ${MACHINE_PLATFORM:MNetBSD-*-i386}
CONFIGURE_ARGS+=	--target=i586-unknown-netbsd
CONFIGURE_ARGS+=	--host=i586-unknown-netbsd
.else
CONFIGURE_ARGS+=	--target=${MACHINE_GNU_PLATFORM}
CONFIGURE_ARGS+=	--host=${MACHINE_GNU_PLATFORM}
.endif

# Do not use uselocale() in third_party/pipewire.
CFLAGS.NetBSD+=	-D__LOCALE_C_ONLY

.if ${MACHINE_ARCH} == "i386"
# This is required for SSE2 code under i386.
CFLAGS+=		-mstackrealign
.endif

PLIST_VARS+=		v4l2_decode
# see toolkit/moz.configure
.if ${MACHINE_ARCH} == "aarch64" || \
    ${MACHINE_ARCH:M*arm*} || \
    ${MACHINE_ARCH} == riscv64
PLIST.v4l2_decode=	yes
.endif

PLIST_VARS+=		ffvpx
# see media/ffvpx/ffvpxcommon.mozbuild
.if ${MACHINE_ARCH} == "aarch64" || \
    ${MACHINE_ARCH:M*arm*} || \
    ${MACHINE_ARCH} == "i386" || \
    ${MACHINE_ARCH} == "x86_64"
PLIST.ffvpx=		yes
.endif

# See ${WRKSRC}/security/sandbox/mac/Sandbox.mm: On Darwin, sandboxing
# support is only available when the toolkit is cairo-cocoa.
CONFIGURE_ARGS.Darwin+=	--disable-sandbox
CONFIGURE_ARGS.NetBSD+=	--disable-sandbox

# The configure test for __thread succeeds, but later we end up with:
# dist/bin/libxul.so: undefined reference to `__tls_get_addr'
CONFIGURE_ENV.NetBSD+=	ac_cv_thread_keyword=no

# RLBox WASM sandbox
.if ${MACHINE_ARCH} == "x86_64" || ${MACHINE_ARCH} == "i386"
# For wasm-ld command
TOOL_DEPENDS+=		lld-[0-9]*:../../devel/lld
.include "../../lang/wasi-libc/buildlink3.mk"
.include "../../lang/wasi-libcxx/buildlink3.mk"
.include "../../lang/wasi-compiler-rt/buildlink3.mk"
CONFIGURE_ARGS+=	--with-wasi-sysroot=${PREFIX}/wasi
CONFIGURE_ENV+=		WASM_CC=${PREFIX}/bin/clang
CONFIGURE_ENV+=		WASM_CXX=${PREFIX}/bin/clang++
.else
CONFIGURE_ARGS+=	--without-wasm-sandboxed-libraries
.endif

SUBST_CLASSES+=		brand
SUBST_STAGE.brand=	pre-configure
SUBST_FILES.brand+=	browser/branding/unofficial/configure.sh
SUBST_FILES.brand+=	browser/branding/unofficial/locales/en-US/brand.properties
SUBST_FILES.brand+=	browser/branding/unofficial/locales/en-US/brand.ftl
SUBST_SED.brand=	-e "s,Nightly,${APP_NAME},g"

INSTALLATION_DIRS+=	share/applications

CHECK_PORTABILITY_SKIP+=	browser/components/loop/run-all-loop-tests.sh
CHECK_PORTABILITY_SKIP+=	browser/extensions/loop/run-all-loop-tests.sh
CHECK_PORTABILITY_SKIP+=	js/src/tests/update-test262.sh
CHECK_PORTABILITY_SKIP+=	modules/pdfium/update.sh
CHECK_PORTABILITY_SKIP+=	security/nss/tests/libpkix/libpkix.sh
CHECK_PORTABILITY_SKIP+=	security/nss/tests/multinit/multinit.sh

CONFIG_GUESS_OVERRIDE+=		build/autoconf/config.guess
CONFIG_GUESS_OVERRIDE+=		js/ctypes/libffi/config.guess
CONFIG_GUESS_OVERRIDE+=		js/src/build/autoconf/config.guess
CONFIG_GUESS_OVERRIDE+=		nsprpub/build/autoconf/config.guess
CONFIG_GUESS_OVERRIDE+=		ldap/sdks/c-sdk/config/autoconf/config.guess
CONFIG_SUB_OVERRIDE+=		build/autoconf/config.sub
CONFIG_SUB_OVERRIDE+=		js/ctypes/libffi/config.sub
CONFIG_SUB_OVERRIDE+=		js/src/build/autoconf/config.sub
CONFIG_SUB_OVERRIDE+=		nsprpub/build/autoconf/config.sub
CONFIG_SUB_OVERRIDE+=		ldap/sdks/c-sdk/config/autoconf/config.sub

CHECK_WRKREF_SKIP+=	lib/firefox/omni.ja

# Should revisit to complete mprotect support.
NOT_PAX_MPROTECT_SAFE+=	lib/${PKGBASE}/firefox

.if defined(FIREFOX_MAINTAINER) && !defined(MAINTAINER_INTERNAL)
TOOL_DEPENDS+=		nodejs-[0-9]*:../../lang/nodejs
USE_TOOLS+=		diff
.else
CONFIGURE_ENV+=		NODEJS="${FILESDIR}/node-wrapper.sh"
.endif

.if defined(FIREFOX_MAINTAINER)
# Create files needed only by the firefox maintainer when updating
# the package
# XXX - manually removing the .*_done files is wrong!
.PHONY: build-list
build-list:
	cd ${WRKSRC}/${OBJDIR}/dist/bin/browser/chrome && \
		find . -type f | sort > ${OUT:Q}

NODE_LIST=	"${WRKDIR}/node.list"
NO_NODE_LIST=	"${WRKDIR}/no-node.list"
NODE_FILES=	"${WRKDIR}/node.flist"

.PHONY: maintainer-files
maintainer-files:
	rm -f ${FILESDIR}/node-wrapper.sh
	V=$$( node -v ) && \
	    printf '#! /bin/sh\n\nVERS=%s\n\nif [ "$$1" = "-v" ] || [ "$$1" = "--version" ]; then\n\tprintf "$${VERS}\\n"\nfi\n\nexit 0\n' $$V \
	    > ${FILESDIR}/node-wrapper.sh && \
	    chmod 0755 ${FILESDIR}/node-wrapper.sh
	rm -f ${WRKDIR}/.build_done ${WRKDIR}/.configure_done
	${MAKE} MAINTAINER_INTERNAL=yes build
	${MAKE} MAINTAINER_INTERNAL=yes OUT="${NO_NODE_LIST}" build-list
	${MAKE} OUT="${NODE_LIST}" build-list
	${DIFF} -u "${NO_NODE_LIST}" "${NODE_LIST}" | \
	    ${AWK} \
	    '/^\+\.\//{ printf("dist/bin/browser/chrome/%s\n", gensub(/^\+\.\//, "", "")) }' \
	    > "${NODE_FILES}"
	cd ${WRKSRC}/${OBJDIR} && tar -c -T "${NODE_FILES}" -z \
	    -f ${FILESDIR}/nodejs-output-${PKGVERSION_NOREV}.tgz
.endif

pre-patch:
	for f in $$(find ${WRKSRC}/third_party/libwebrtc -name moz.build -type f) ; \
	do \
		${AWK} -f ${FILESDIR}/replace-moz.build.awk $$f > $$f.new; mv $$f.new $$f ; \
	done

pre-configure:
	cd ${WRKSRC} && mkdir ${OBJDIR}
	${SED}	-e "s/@MOZ_APP_DISPLAYNAME@/${APP_NAME}/g" \
		-e 's/@MOZ_APP_NAME@/firefox/g' \
		-e 's/@StartupWMClass@/firefox/g' \
		${WRKSRC}/toolkit/mozapps/installer/linux/rpm/mozilla.desktop > \
		${WRKDIR}/firefox.desktop
.if !defined(FIREFOX_MAINTAINER)
	mv ${WRKDIR}/dist ${WRKSRC}/${OBJDIR}
.endif

post-install:
	${RM} -f ${DESTDIR}${PREFIX}/bin/firefox
	${ECHO} '#! /bin/sh' > ${DESTDIR}${PREFIX}/bin/firefox
	${ECHO} '${PREFIX}/lib/firefox/firefox "$$@"' >> \
		${DESTDIR}${PREFIX}/bin/firefox
	${CHMOD} 755 ${DESTDIR}${PREFIX}/bin/firefox
	${INSTALL_DATA} ${WRKDIR}/firefox.desktop \
		${DESTDIR}${PREFIX}/share/applications/firefox.desktop
.for s in 16 22 24 32 48 64 128 256
	${INSTALL_DATA_DIR} ${DESTDIR}${PREFIX}/share/icons/hicolor/${s}x${s}/apps
	${INSTALL_DATA} ${WRKSRC}/browser/branding/unofficial/default${s}.png \
		${DESTDIR}${PREFIX}/share/icons/hicolor/${s}x${s}/apps/firefox.png
.endfor

# Makefiles sometimes call "rm -f" without more arguments. Kludge around ...
.PHONY: create-rm-wrapper
pre-configure: create-rm-wrapper
create-rm-wrapper:
	printf '#!/bin/sh\n[ "$$*" = "-f" ] && exit 0\nexec /bin/rm $$@\n' > \
	  ${WRAPPER_DIR}/bin/rm
	chmod +x ${WRAPPER_DIR}/bin/rm

do-test:
	cd ${WRKSRC}/${OBJDIR}/dist/bin &&	\
	     ./run-mozilla.sh ${WRKSRC}/mach check-spidermonkey

.include "options.mk"
.include "../../mk/atomic64.mk"
.include "../../devel/libffi/buildlink3.mk"
.include "../../devel/nspr/buildlink3.mk"
BUILDLINK_API_DEPENDS.nspr+=	nspr>=4.18
.include "../../devel/nss/buildlink3.mk"
.include "../../devel/zlib/buildlink3.mk"
.include "../../graphics/hicolor-icon-theme/buildlink3.mk"
.include "../../graphics/libwebp/buildlink3.mk"
BUILDLINK_DEPMETHOD.clang=	build
.include "../../lang/clang/buildlink3.mk"
RUST_REQ=	1.23.0
.include "../../lang/rust/rust.mk"
.include "../../net/libIDL/buildlink3.mk"
.include "../../multimedia/ffmpeg7/buildlink3.mk"
.include "../../multimedia/libvpx/buildlink3.mk"
.include "../../sysutils/desktop-file-utils/desktopdb.mk"
.if ${OPSYS} != "Darwin"
.  include "../../graphics/MesaLib/buildlink3.mk"
.endif
.include "../../x11/gtk3/buildlink3.mk"
PLIST_VARS+=		wayland
.if ${PKG_BUILD_OPTIONS.gtk3:Mwayland}
PLIST.wayland=		yes
.endif
.include "../../x11/libXt/buildlink3.mk"
.include "../../mk/bsd.pkg.mk"
