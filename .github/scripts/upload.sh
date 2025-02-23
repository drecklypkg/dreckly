#!/usr/bin/env bash
#
# Upload a packages directory to remote host for BINPKG_SITES.
#

set -eux

. $(dirname $0)/common.sh

# This script is often called regardless of whether the previous step
# completed successfully or not (so that we still get to keep any packages
# that did build), but if nothing built then exit early and successfully.
#
if [ ! -d ${CI_PACKAGES} ]; then
	exit
fi

PATH="${CI_SYSTEM_PATH}"

if ${CLEAR_BINPKG_CACHE}; then
	RSYNC_DELETE="--delete"
else
	RSYNC_DELETE=
fi

# On Windows we can't use rsync, only the "native" SSH has access to the
# GitHub secrets, and Cygwin rsync does not work with the native SSH.
#
case "$(uname)" in
CYGWIN*)
	ssh ${CI_SSH_USER}@${CI_SSH_HOST} "
		if ${CLEAR_BINPKG_CACHE}; then
			rm -rf ${CI_REMOTE_DIR}
		fi
		mkdir -p ${CI_REMOTE_DIR}"
	# The native ssh/scp cannot use Cygwin paths so change to the parent
	# directory first to avoid complications.
	cd ${CI_PACKAGES}
	scp -rp All ${CI_SSH_USER}@${CI_SSH_HOST}:${CI_REMOTE_DIR}/
	;;
*)
	rsync -av ${RSYNC_DELETE} --exclude .cvsignore \
	    ${CI_PACKAGES}/ \
	    ${CI_SSH_USER}@${CI_SSH_HOST}:${CI_REMOTE_DIR}
	;;
esac
