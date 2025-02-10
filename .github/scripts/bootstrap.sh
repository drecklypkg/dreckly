#!/usr/bin/env bash
#
# Bootstrap a dreckly prefix.
#


#
# Script is executed from within the dreckly checkout.  To simplify path
# settings across all OS (i.e. Cygwin), calculate our own variables.  We
# will put everything in DRECKLY_WORKSPACE to keep things simple, and use
# pwd -P explicitly here to avoid any later issues with buildlink symlinks.
#
DRECKLY_WORKSPACE=$(cd ..; pwd -P)
DRECKLY_SRCDIR=$(pwd -P)

# Putting the bootstrap tar inside the checkout isn't ideal but due to
# limitations in actions/cache it has to exist there for it to be picked up.
BOOTSTRAP_KIT="${DRECKLY_SRCDIR}/bootstrap.tar"
PREFIX="${DRECKLY_WORKSPACE}/pkg"

case "$(uname)" in
CYGWIN*)
	PATH="/cygdrive/c/tools/cygwin/bin"
	;;
NetBSD)
	# As these differences are often missed by NetBSD developers, enforce
	# them for these NetBSD builds.
	BOOTSTRAP_ARGS="--pkginfodir=share/info --pkgmandir=share/man --prefer-pkgsrc=yes"
	;;
esac

cat >${DRECKLY_WORKSPACE}/bootstrap-include.mk <<EOF
MAKE_JOBS=4
EOF

#
# This really needs to go in mk/tools at some point, but needs better
# understanding of what is shipped by default and how to detect the
# path correctly.
#
case "$(uname)" in
CYGWIN*)
	cat >>${DRECKLY_WORKSPACE}/bootstrap-include.mk <<-EOF
		FETCH_USING=		curl
		TOOLS_PLATFORM.curl=	/cygdrive/c/msys64/usr/bin/curl
	EOF
	;;
esac

cd ${DRECKLY_SRCDIR}/bootstrap
./bootstrap ${BOOTSTRAP_ARGS} \
	--binary-kit=${BOOTSTRAP_KIT} \
	--make-jobs=4 \
	--mk-fragment=${DRECKLY_WORKSPACE}/bootstrap-include.mk \
	--prefix=${PREFIX} \
	--unprivileged \
	--workdir=${DRECKLY_WORKSPACE}/wrkdir
