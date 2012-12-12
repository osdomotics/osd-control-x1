############################ -*- Mode: Makefile -*- ###########################
## local-vars.mk --- 
## Author           : Manoj Srivastava ( srivasta@glaurung.green-gryphon.com ) 
## Created On       : Sat Nov 15 10:43:00 2003
## Created On Node  : glaurung.green-gryphon.com
## Last Modified By : Manoj Srivastava
## Last Modified On : Wed Dec  3 23:16:54 2003
## Last Machine Used: glaurung.green-gryphon.com
## Update Count     : 19
## Status           : Unknown, Use with caution!
## HISTORY          : 
## Description      : 
## 
## arch-tag: 1a76a87e-7af5-424a-a30d-61660c8f243e
## 
###############################################################################

FILES_TO_CLEAN  = TAGS tags debian/files debian/substvars ChangeLog flex.spec 
STAMPS_TO_CLEAN = 
DIRS_TO_CLEAN   = doc/flex.html debian/stamp

# Location of the source dir
SRCTOP    := $(shell if [ "$$PWD" != "" ]; then echo $$PWD; else pwd; fi)
TMPTOP     = $(SRCTOP)/debian/$(package)
LINTIANDIR = $(TMPTOP)/usr/share/lintian/overrides
DOCBASEDIR = $(TMPTOP)/usr/share/doc-base
MENUDIR    = $(TMPTOP)/usr/share/menu


BINDIR  = $(TMPTOP)$(PREFIX)/bin
LIBDIR  = $(TMPTOP)$(PREFIX)/lib
MANDIR  = $(TMPTOP)$(PREFIX)/share/man
DOCDIR  = $(TMPTOP)$(PREFIX)/share/doc/$(package)
INFODIR = $(TMPTOP)$(PREFIX)/share/info
DOCTOP  = $(TMPTOP)/usr/share/doc
MAN1DIR = $(MANDIR)/man1
MAN3DIR = $(MANDIR)/man3
MAN5DIR = $(MANDIR)/man5
MAN7DIR = $(MANDIR)/man7
MAN8DIR = $(MANDIR)/man8

define checkdir
	@test -f debian/rules -a -f flexdef.h || \
          (echo Not in correct source directory; exit 1)
endef

define checkroot
	@test $$(id -u) = 0 || (echo need root priviledges; exit 1)
endef
