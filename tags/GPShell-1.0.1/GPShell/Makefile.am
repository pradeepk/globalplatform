## Process this file with automake to produce Makefile.in

bin_PROGRAMS = gpshell

gpshell_SOURCES = GPShell.c
gpshell_CPPFLAGS = $(AM_CPPFLAGS) $(PCSCLITE_CFLAGS)
gpshell_LDADD = $(AM_CPPFLAGS) -lOpenPlatform

EXTRA_DIST = GPShell.dep GPShell.dsp GPShell.dsw GPShell.mak stdafx.c \
stdafx.h reconf list.txt helloDelete.txt helloInstall.txt HelloWorld.bin \
HelloWorld.cap

MAINTAINERCLEANFILES = \
	Makefile.in \
	configure \
	aclocal.m4 \
	aux/install-sh \
	aux/missing \
	aux/config.guess \
	aux/config.sub \
	aux/compile \
	aux/depcomp

