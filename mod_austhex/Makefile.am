# $Id$


AUTOGEN=@AUTOGEN@


# Our target (the module itself)
lib_LTLIBRARIES=\
	mod_austhex.la


# Include dir
INCLUDES=\
	-I$(top_srcdir)/src


# Source files..
mod_austhex_la_SOURCES=\
	src/autoconf.h \
	src/module.cpp


# Flags used when linking the module (we want a module, not a library)
mod_austhex_la_LDFLAGS=\
	-avoid-version \
	-module


# Libraries we need..
mod_austhex_la_LIBADD=\
	-lkineircd \
	-lkineircd_irc2


# Extra stuff to distribute in this package
EXTRA_DIST=\
	autogen/language.def \
	doc/example.conf \
	install/language.tpl \
	misc/austrace


# Rule to build the language '.lang' files (.lang is a fake file)
install/.lang: install/language.tpl autogen/language.def
	$(AUTOGEN) \
		-b install/ \
		-T install/language.tpl \
		autogen/language.def


# Stuff that needs to be make prior to the dependancy files being built
BUILT_SOURCES=\
	install/.lang
