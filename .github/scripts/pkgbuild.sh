#!/usr/bin/env bash
#
# Wrapper script to build a set of packages.
#

set -eux

. $(dirname $0)/common.sh

PATH="${CI_PREFIX}/sbin:${CI_PREFIX}/bin:${CI_SYSTEM_PATH}"

# Ensure we start with clean work areas.  Some packages can leave directories
# with insufficient permissions so we need to ensure they are fixed-up first.
#
chmod -R u+w ${CI_PREFIX} ${CI_TMPDIR} ${CI_WRKDIR} 2>/dev/null || true
rm -rf ${CI_PACKAGES} ${CI_PREFIX} ${CI_TMPDIR} ${CI_WRKDIR}
mkdir -p ${CI_TMPDIR}

# Avoid any interactive prompts which can hang builds.
export BATCH=1

# BINPKG_SITES should be set to the correct URL, ensure it's exported.
export BINPKG_SITES
export DEPENDS_TARGET=bin-install

export DISTDIR="${CI_DISTDIR}"
export PACKAGES="${CI_PACKAGES}"
export WRKOBJDIR="${CI_WRKDIR}"

# Build a package using a clean prefix, extracting a fresh bootstrap kit for
# each build so that conflicting packages can be built in the same run.
#
build_pkg() {
	pkgdir=$1; shift

	rm -rf ${CI_PREFIX} ${CI_WRKDIR}
	${CI_CMD_TAR} -xpf ${CI_BOOTSTRAP_KIT} -C /

	logfile=${WRKOBJDIR}/${pkgdir}/bmake.log
	mkdir -p ${WRKOBJDIR}/${pkgdir}

	(
		set -o pipefail
		cd ${pkgdir}
		bmake install 2>&1 | tee ${logfile} && bmake clean
	)
}

# PKGBUILD_FILES contains a list of files that were modified by the commit for
# testing.  We extract a uniq list of package directories from it and build
# them.  This is pretty basic, no ordering or whatever, but it'll do for now.
#
for file in ${PKGBUILD_FILES}; do
	echo ${file} | cut -d/ -f1,2
done | sort | uniq | while read dir; do
	if [ -f ${dir}/Makefile ]; then
		build_pkg ${dir}
	fi
done
