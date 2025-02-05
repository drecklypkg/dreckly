#!/usr/bin/env bash
#
# Wrapper script helps to consolidate per-platform configuration.
#

BINARY_KIT=${GITHUB_WORKSPACE}/bootstrap.tar
case "$(uname)" in
CYGWIN*)
	PATH=/cygdrive/c/tools/cygwin/bin
	BINARY_KIT=$(cygpath ${GITHUB_WORKSPACE})/bootstrap.tar
	;;
NetBSD)
	# As these differences are often missed by NetBSD developers, enforce
	# them for these NetBSD builds.
	BOOTSTRAP_ARGS="--pkginfodir=share/info --pkgmandir=share/man --prefer-pkgsrc=yes"
	;;
esac

cat >${HOME}/bootstrap-include.mk <<EOF
MAKE_JOBS=4
EOF

cd ${GITHUB_WORKSPACE}/bootstrap
./bootstrap ${BOOTSTRAP_ARGS} \
	--binary-kit=${BINARY_KIT} \
	--make-jobs=4 \
	--mk-fragment=${HOME}/bootstrap-include.mk \
	--prefix=${HOME}/pkg \
	--unprivileged \
	--workdir=${HOME}/wrkdir
