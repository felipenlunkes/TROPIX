First examine global.h and Fvwm.tmpl and change any of the defaults
that you need to.  Now, if you have Imake installed on your system,
just run "xmkmf;make Makefiles" (or ./MakeMakefiles) to build all of
the makefiles, then run make.  You'll need an ANSI C compiler to do
this, by the way (i.e. don't use cc under SunOS, but use acc or gcc
instead).

Then you can run 'make install' and 'make install.man' to install it
where you specified, but it doesn't have to be officially installed to
run it.

If you don't have Imake installed, then you'll probably have to get
the makefiles that someone else used for your platform, or get Imake
from ftp.x.org.  See the FAQ as well for info on this.

Note: plans are in the works to switch to GNU Autoconf scripts to
configure the makefiles which should make it even more portable and
easy to build.  I may also include 'standard' simple makefiles that
should work with a small amount of editing, if I get a chance.

Also, there is an 'extras' directory that contains some modules that
don't get built automatically.  Feel free to look at those if you'd
like, but you'll have to do those by hand.  The FvwmConfig module is
in there because it's written in C++ and Imake (before X11R6) doesn't
support C++.  There is a makefile (Makefile.std) in that directory
that you can hand edit and hand build the module for your system, if
desired.  There is an Imakefile, but it will probably only work under
X11R6, which has C++ support in Imake.

FVWM should build under most modern Unix flavors.  The platforms that
I know or believe FVWM has been built under are:
        Linux
        FreeBSD
        NetBSD
        AIX (3.2.[45], 4.1.X)
        SunOS (4.1.3)
        Solaris (2.[45])
        HP-UX (9, maybe 10)
        Dec Alpha OSF/1 & OSF/2
        Ultrix 4.4
        Irix 5.3
        Irix 6.2
        Sony NWS1250 with NEWSOS 4.1C
        OS/2 Warp w/ XF86 port (needed some tweaking)
        UXP/DS V20L10(SVR4.2) (Fujitsu FS/90 workstation)

