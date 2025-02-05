dreckly
=======

dreckly is a framework for building software for a variety of UNIX-like
systems.  dreckly is a fork of pkgsrc, with a specific focus on the following
values:

  * Stability.  One of our major frustrations with pkgsrc is that the value
    that is prioritised above all is velocity.  The culture is very much "move
    fast and break things", and packages are frequently updated to bleeding
    edge releases, regardless of whether all packages that depend on them will
    continue to build correctly.  Adding large patchsets to fix dependent
    packages significantly bloats the repository.  The high rate of churn also
    results in users having to frequently rebuild the majority of their
    packages, and makes bulk builds of all packages take days, if not weeks
    for older architectures.

  * Portability.  pkgsrc claims to support over 20 operating systems, however
    in reality the quality of that support varies dramatically, with some
    systems unable to even bootstrap.  The majority of pkgsrc developers only
    test on NetBSD, and packages are frequently left broken on other platforms,
    leaving other developers to spend the majority of their time cleaning up
    after them and fixing regressions, rather than working on new features or
    improving support.

  * Quality.  All changes to dreckly must be reviewed by another developer, and
    tested prior to integration.  pkglint must be clean.  Code should be
    readable, comments should be specific and focused, and not rambly or
    littered with opinions or unnecessary "XXX".  No work-in-progress.  It
    should be a joy for anyone to open an existing package and start hacking.

Dreckly is a Cornish word that means a task will be done at some point in the
future.  "I'll do it dreckly."  There's no mad rush to do it as quickly as
possible, it'll be done when it's done.  Quality takes time and consideration.
This is very much our ethos.

Bootstrapping
-------------

To use dreckly, you first need to bootstrap:

	cd bootstrap
	./bootstrap

Note that this is only for the most simple case, using all defaults.

Please consult `bootstrap/README` and `bootstrap/README.OS` for detailed
information about bootstrapping.

Building packages
-----------------

	cd category/package-name
	$PREFIX/bin/bmake install

Where `$PREFIX` is where you've chosen to install packages
(typically `/usr/pkg`)

On NetBSD, `bmake` is simply the built-in `make` tool.

To build packages in bulk, tools such as `pkgtools/pbulk` and
`pkgtools/pkg_comp` can be used.

Community / Troubleshooting
---------------------------

- Join the community IRC channel [#dreckly @ libera.chat](https://web.libera.chat/#dreckly).
- Pull requests and issues are welcome!

Additional links
----------------

Tutorials and guides related to pkgsrc are still applicable to dreckly.

- [pkgsrc guide](https://www.NetBSD.org/docs/pkgsrc/) - the authoritative document on pkgsrc, also available as `doc/pkgsrc.txt`
- [pkgsrc in the NetBSD Wiki](https://wiki.NetBSD.org/pkgsrc/) - miscellaneous articles and tutorials
- [pkgsrc.se](https://pkgsrc.se/) - a searchable web index of pkgsrc
- [pkgsrc-wip](https://pkgsrc.org/wip/) - a project to get more people actively involved with creating packages for pkgsrc
- [pkgsrc on Twitter](https://twitter.com/pkgsrc) - announcements to the world
- [pkgsrcCon](https://pkgsrc.org/pkgsrcCon) - we get together
- [BulkTracker](https://releng.netbsd.org/bulktracker/) - a web application that tracks pkgsrc bulk builds
