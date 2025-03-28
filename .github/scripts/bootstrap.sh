#!/usr/bin/env bash
#
# Bootstrap a prefix.
#

set -eux

. $(dirname $0)/common.sh

# In many places we only run this script if we already detected that we need
# to generate a bootstrap kit, but adding an early bailout helps other places
# where it is simpler to just run the script and let it figure out what to do.
#
if [ -f ${CI_BOOTSTRAP_KIT} ]; then
	echo "Bootstrap kit ${CI_BOOTSTRAP_KIT} already exists."
	exit 0
fi

PATH="${CI_SYSTEM_PATH}"

# Ensure we start with clean work areas.  CI_PREFIX and CI_WRKDIR must not
# exist, bootstrap will create them.  Some packages can leave directories with
# insufficient permissions so we need to ensure they are fixed-up first.
#
chmod -R u+w ${CI_PREFIX} ${CI_TMPDIR} ${CI_WRKDIR} 2>/dev/null || true
rm -rf ${CI_PREFIX} ${CI_TMPDIR} ${CI_WRKDIR}
mkdir -p ${CI_TMPDIR}

bootstrap_args=

# Set up OS-specific variables.
case "$(uname)" in
NetBSD)
	# As these differences are often missed by NetBSD developers, enforce
	# them for these NetBSD builds.
	bootstrap_args="${bootstrap_args} --pkginfodir=share/info"
	bootstrap_args="${bootstrap_args} --pkgmandir=share/man"
	bootstrap_args="${bootstrap_args} --prefer-pkgsrc=yes"
	;;
esac

cat >${CI_TMPDIR}/bootstrap-include.mk <<EOF
ALLOW_VULNERABLE_PACKAGES=	yes
FAILOVER_FETCH=			yes
MAKE_JOBS=			4
NO_PKGTOOLS_REQD_CHECK=		yes
PKG_DEVELOPER=			yes
SKIP_LICENSE_CHECK=		yes
USE_INDIRECT_DEPENDS=		yes
X11_TYPE=			modular
EOF

# This really needs to go in mk/tools at some point, but needs better
# understanding of what is shipped by default and how to detect the
# path correctly.
#
case "$(uname)" in
CYGWIN*)
	cat >>${CI_TMPDIR}/bootstrap-include.mk <<-EOF
		# OS-specific overrides
		FETCH_USING=			curl
		TOOLS_PLATFORM.curl=		/cygdrive/c/msys64/usr/bin/curl
	EOF
	;;
esac

mkdir -p $(dirname ${CI_BOOTSTRAP_KIT})
cd ${CI_SRCDIR}/bootstrap
./bootstrap ${bootstrap_args} \
	--binary-kit=${CI_BOOTSTRAP_KIT} \
	--make-jobs=4 \
	--mk-fragment=${CI_TMPDIR}/bootstrap-include.mk \
	--prefix=${CI_PREFIX} \
	--unprivileged \
	--workdir=${CI_WRKDIR}
