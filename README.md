dreckly
=======

dreckly is a framework for building software for a variety of UNIX-like
systems.  dreckly is a fork of pkgsrc, with a specific focus on the following:

  * **Portability** - pkgsrc has grown to focus more on providing as many
    bleeding-edge packages as possible for the most recent releases of NetBSD.
    Instead, dreckly focuses on providing a tight collection of mature packages
    that are expected to work everywhere.
  * **Bootstrappability** - dreckly stays focused on supporting C99 compilers
    to allow bootstrapping on any Unix-like system, without growing low-level
    dependencies on the latest C++2x and Rust compilers.
  * **Stability** - rejecting the "unstable -current" strategy, with an aim
    towards building a useful collection of software packages that moves slowly
    and prioritizes avoiding breaking changes. We prefer long-term support
    versions of packages where possible, and avoid the need for constant
    recursive revbumps, keeping updates small and rebuilds infrequent.

Further background on our mission and values can be found
[here](https://github.com/drecklypkg/dreckly/discussions/5).

Dreckly is a Cornish word that means a task will be done at some point in the
future.  "I'll do it dreckly".  There's no mad rush to do things as quickly as
possible, with no thought to the consequences.  Quality takes time and
consideration.  This is very much our ethos.

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
