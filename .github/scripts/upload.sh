#!/usr/bin/env bash
#
# Upload a packages directory to remote host for BINPKG_SITES.
#

set -eux

. $(dirname $0)/common.sh

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
	scp -rp ${CI_PACKAGES}/All ${CI_SSH_USER}@${CI_SSH_HOST}:${CI_REMOTE_DIR}/
	;;
*)
	rsync -av ${RSYNC_DELETE} --exclude .cvsignore \
	    ${CI_PACKAGES}/ \
	    ${CI_SSH_USER}@${CI_SSH_HOST}:${CI_REMOTE_DIR}
	;;
esac
