# $NetBSD: utility.mk,v 1.3 2013/05/12 05:13:37 obache Exp $

# The 'info' target can be used to display information about a package.
.PHONY: info
info:
	${RUN}${PKG_INFO} "${PKGWILDCARD}"

# The 'check' target can be used to check an installed package.
.PHONY: check
check:
	${RUN}${PKG_ADMIN} check "${PKGWILDCARD}"

# The 'list' target can be used to list the files installed by a package.
.PHONY: list
list:
	${RUN}${PKG_INFO} -L "${PKGWILDCARD}"

######################################################################
###
### The targets below should probably be removed from pkgsrc.
###
######################################################################

# show-downlevel:
#	Lists the packages whose installed version does not match the
#	current version in pkgsrc.
#
show-downlevel: .PHONY
.if defined(PKG_FAIL_REASON)
	${RUN}${DO_NADA}
.else
	${RUN}								\
	found="`${PKG_INFO} -E \"${PKGWILDCARD}\" || ${TRUE}`";		\
	if [ "X$$found" != "X" -a "X$$found" != "X${PKGNAME}" ]; then	\
		${ECHO} "${PKGBASE} package: $$found installed, pkgsrc version ${PKGNAME}"; \
		if [ "X$$STOP_DOWNLEVEL_AFTER_FIRST" != "X" ]; then	\
			${ECHO} "stopping after first downlevel pkg found"; \
			exit 1;						\
		fi;							\
	fi
.endif

.PHONY: show-installed-depends
show-installed-depends:
.if !empty(DEPENDS)
	${RUN}								\
	for i in ${DEPENDS:C/:.*$//:Q:S/\ / /g} ; do			\
		echo "$$i =>" `${PKG_INFO} -E "$$i"`;			\
	done
.endif

# Short aliases
.PHONY: sid
sid: show-installed-depends
