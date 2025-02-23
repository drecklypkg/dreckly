#!/usr/bin/env bash
#
# Set up common variables shared across both GitHub runners and Jenkins
# clients.  There are a number of differences between them, and due to
# limitations in e.g. the actions cache plugin we can't just use standard
# temporary directories etc.
#
# Prefix everything with CI_ so it's easy to identify in script output.
#
#	CI_BOOTSTRAP_KIT	Path to hashed bootstrap.tar
#	CI_DISTDIR		Path to distfiles
#	CI_PACKAGES		Path to PACKAGES
#	CI_PREFIX		Bootstrap --prefix / LOCALBASE
#	CI_SRCDIR		Read-only dreckly/pkgsrc checkout
#	CI_SYSTEM_PATH		Per-OS PATH without prefix
#	CI_TMPDIR		Temporary directory
#	CI_WORKSPACE		Writeable work directory
#	CI_WRKDIR		Writeable saved work area (WRKOBJDIR etc)
#
#	CI_CMD_TAR		GNU tar or similar
#
# Note that GitHub VMs do NOT have the standard GITHUB_* variables set, so
# we key whether we're running in GitHub or Jenkins based on the Jenkins
# WORKSPACE variable.
#

if [ -n "${WORKSPACE:-}" ]; then
	# Jenkins clients execute this script as the 'ci' user.  At present to
	# keep things simple the builds are not chrooted and re-use the same
	# home directory, so be careful to avoid any pollution from previous
	# builds.
	CI_WORKSPACE="${HOME}"
	CI_SRCDIR="${WORKSPACE}"

	CI_BOOTSTRAP_KIT="${CI_WORKSPACE}/bootstrap/${BOOTSTRAP_HASH}/bootstrap.tar"
	CI_WRKDIR="${CI_WORKSPACE}/wrkdir"
else
	# GitHub runners are executed from within the checkout.  To simplify
	# path settings across all OS (i.e. Cygwin) calculate variables using
	# pwd, and explicitly use -P to avoid buildlink symlink issues.
	CI_WORKSPACE=$(cd ..; pwd -P)
	CI_SRCDIR=$(pwd -P)

	# This has to live inside the default directory for the cache action
	# to correctly handle it.  All of the BOOTSTRAP_HASH logic is handled
	# there.
	CI_BOOTSTRAP_KIT="${CI_SRCDIR}/bootstrap.tar"

	# Again for simplicity of supporting actions/upload-artifact the work
	# directories live under CI_SRCDIR.
	CI_WRKDIR="${CI_SRCDIR}/wrkdir"
fi

CI_DISTDIR="${CI_WORKSPACE}/distfiles"
CI_PACKAGES="${CI_WORKSPACE}/packages"
CI_PREFIX="${CI_WORKSPACE}/pkg"
CI_TMPDIR="${CI_WORKSPACE}/tmp"

CI_SYSTEM_PATH="/sbin:/bin:/usr/sbin:/usr/bin"

CI_CMD_TAR=tar

case "$(uname)" in
CYGWIN*)
	CI_SYSTEM_PATH="/cygdrive/c/tools/cygwin/bin:/cygdrive/c/Windows/System32/OpenSSH"
	;;
SunOS)
	CI_CMD_TAR=gtar
	CI_SYSTEM_PATH="/sbin:/usr/sbin:/usr/bin:/opt/local/sbin:/opt/local/bin"
	;;
esac
