#!/usr/bin/env bash
#
# Wrapper script to build a set of packages.
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

#
# Unpack bootstrap kit if we don't have it already unpacked from a previous
# build session.  Obviously requires that a prior step puts it in place.
#
if [ ! -d ${PREFIX} ]; then
	tar -xvf ${BOOTSTRAP_KIT} -C /
fi

# USE_BINPKG is set to true or false in the environment via input variables.
# BINPKG_SITES is set to the correct URL, all we do is ensure it's exported
# if we're using them, otherwise ensure it's unset.
if ${USE_BINPKG}; then
	export BINPKG_SITES
	export DEPENDS_TARGET=bin-install
else
	unset BINPKG_SITES
fi

PATH=${PREFIX}/sbin:${PREFIX}/bin:/usr/sbin:/sbin:/usr/bin:/bin

# INPUT_FILES contains a list of files that were modified by the commit for
# testing.  We extract a uniq list of package directories from it and build
# them.  This is pretty basic, no ordering or whatever, but it'll do for now.
#
export WRKOBJDIR=${DRECKLY_WORKSPACE}/wrkdir
mkdir -p ${WRKOBJDIR}

for file in ${INPUT_FILES}; do
	echo ${file} | cut -d/ -f1,2
done | sort | uniq | while read dir; do
	logfile=${WRKOBJDIR}/${dir}/bmake.log
	mkdir -p ${WRKOBJDIR}/${dir}
	(
		set -o pipefail
		cd ${dir}
		bmake install 2>&1 | tee ${logfile} && bmake clean
	)
done
