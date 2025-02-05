#!/usr/bin/env bash

set -x

if ${CLEAR_BINPKG_CACHE}; then
	RSYNC_DELETE="--delete"
else
	RSYNC_DELETE=
fi

#
# Annoyingly rsync doesn't work for some reason on Cygwin, with nothing more
# helpful than "connection unexpectedly closed", even though ssh works fine
# as per the below.
#
case "$(uname)" in
CYGWIN*)
	ssh ${CI_SSH_USER}@${CI_SSH_HOST} "
		if ${CLEAR_BINPKG_CACHE}; then
			rm -rf ${CI_REMOTE_DIR}
		fi
		mkdir -p ${CI_REMOTE_DIR}"
	scp -rp ./packages/All ${CI_SSH_USER}@${CI_SSH_HOST}:${CI_REMOTE_DIR}/
	;;
*)
	rsync -av ${RSYNC_DELETE} --exclude .cvsignore \
	    ./packages/ \
	    ${CI_SSH_USER}@${CI_SSH_HOST}:${CI_REMOTE_DIR}
	;;
esac
