# Makefile for bulk-core, the most essential set of packages required.

DISTNAME=	bulk-core-20250212
CATEGORIES=	meta-pkgs
MASTER_SITES=	# empty
DISTFILES=	# empty

MAINTAINER=	jperkin@smartos.org
COMMENT=	Meta-package for testing core packages

META_PACKAGE=	yes

RESTRICTED=		Just for test build purposes
NO_BIN_ON_CDROM=	${RESTRICTED}
NO_BIN_ON_FTP=		${RESTRICTED}

.include "../../mk/bsd.prefs.mk"

DEPENDS+=	apache>0:../../www/apache24
DEPENDS+=	coreutils>0:../../sysutils/coreutils
DEPENDS+=	curl>0:../../www/curl
DEPENDS+=	cvs>0:../../devel/scmcvs
DEPENDS+=	dovecot>0:../../mail/dovecot2
DEPENDS+=	emacs-nox11>0:../../editors/emacs-nox11
DEPENDS+=	fetch>0:../../net/fetch
DEPENDS+=	git-base>0:../../devel/git-base
DEPENDS+=	gsed>0:../../textproc/gsed
DEPENDS+=	lintpkgsrc>0:../../pkgtools/lintpkgsrc
DEPENDS+=	m4>0:../../devel/m4
DEPENDS+=	mozilla-rootcerts-openssl>0:../../security/mozilla-rootcerts-openssl
DEPENDS+=	mutt>0:../../mail/mutt
DEPENDS+=	nano>0:../../editors/nano
DEPENDS+=	nginx>0:../../www/nginx
DEPENDS+=	nmap>0:../../net/nmap
DEPENDS+=	pkg_alternatives>0:../../pkgtools/pkg_alternatives
DEPENDS+=	pkgdiff>0:../../pkgtools/pkgdiff
DEPENDS+=	pkgin>0:../../pkgtools/pkgin
DEPENDS+=	rsync>0:../../net/rsync
DEPENDS+=	screen>0:../../misc/screen
DEPENDS+=	tmux>0:../../misc/tmux
DEPENDS+=	vim>0:../../editors/vim

#
# For languages, only pull in the default version for each platform.
#
LUA_VERSIONS_ACCEPTED=		${LUA_VERSION_DEFAULT}
PHP_VERSIONS_ACCEPTED=		${PHP_VERSION_DEFAULT}
PKG_APACHE_ACCEPTED=		${PKG_APACHE_DEFAULT}
PYTHON_VERSIONS_ACCEPTED=	${PYTHON_VERSION_DEFAULT}
RUBY_VERSIONS_ACCEPTED=		${RUBY_VERSION_DEFAULT}

.include "../../lang/lua/buildlink3.mk"
.include "../../lang/perl5/buildlink3.mk"
.include "../../lang/php/phpversion.mk"
.include "${PHPPKGSRCDIR}/buildlink3.mk"
.include "../../lang/python/pyversion.mk"
.include "../../lang/ruby/buildlink3.mk"
.include "../../mk/bsd.pkg.mk"
