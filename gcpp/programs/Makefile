#!/usr/bin/make -f
# file: programs/Makefile 

# ====================================================================
# folders;
# --------------------------------------------------------------------

include ../make.def

# ====================================================================
# symbols;
# --------------------------------------------------------------------

CFLAGS=-Wall -D_GNU_SOURCE -DMAKEFILE
LFLAGS=
TOOLS=call2 cblock2 cdep2 cfm cmpp csstidy ctidy ctokens dnstidy javatidy mmf2 order2 phptidy pkg relate2 sqltidy tokens defix profile page calend2 chtml index htmltidy mptidy
# TOOLS+=syslog2 
VPATH=../classes:../linux
TRASH=*~ *.[0-9][0-9][0-9] t t.* *.exe *.o *.html *.css
PAGES=cfm.1 ctidy.1 javatidy.1 csstidy.1 htmltidy.1 mptidy.1 phptidy.1

# ====================================================================
# targets;
# --------------------------------------------------------------------

compile: ${TOOLS}
scripts:
manuals:
	install -m 0444 -o ${OWNER} -g ${GROUP} ${PAGES} ${MAN}
install: compile
	install -m 0555 -o ${OWNER} -g ${GROUP} ${TOOLS} ${BIN}
library:
	install -m 6755 -o ${OWNER} -g ${GROUP} -d ${BIN}
fresh: clean compile
clean:
	rm -f ${TOOLS} ${TRASH}
	chmod 0644 *.cpp *.txt *.1
	chmod 0755 Makefile *.sh 
check:
	${SH} programs.sh
ignore:
	echo ${TOOLS} | tr " " "\n" > .gitignore

# ====================================================================
# targets;
# --------------------------------------------------------------------

calend2: calend2.o ogetoptv.o oputoptv.o oversion.o otext.o ocalendar.o omonth.o odate.o oindex.o oindent.o
call2: call2.o ogetoptv.o oputoptv.o oversion.o oerror.o oascii.o ocpluswords.o okeywords.o oflagword.o owildcard.o ofileopen.o ofilespec.o opathspec.o ocontext.o odiscard.o otext.o
cblock: cblock.o ogetoptv.o oputoptv.o oversion.o oerror.o ofileopen.o ofilespec.o opathspec.o ocontext.o owildcard.o oescape.o ocollect.o oascii.o ocblock.o otext.o
cfm: cfm.o ogetoptv.o oputoptv.o oversion.o oflagword.o ofileopen.o ofilespec.o ocontext.o owildcard.o oescape.o oerror.o opathspec.o octidy.o ocomment.o oinclude.o oprofile.o oswitch.o ocgotowords.o ocexitwords.o okeywords.o oascii.o oindent.o ocollect.o otext.o
chtml: chtml.o ogetoptv.o oputoptv.o oversion.o ofilespec.o opathspec.o owildcard.o ocontext.o oerror.o oitem.o olist.o oglossary.o owebpage.o oindent.o oenviron.o oattribute.o oscantext.o ocursor.o ochrtbl.o ochrlwr.o ochrupr.o oscancode.o ochtml.o okeywords.o oclangwords.o ocpluswords.o ocprocwords.o oISOGlyph.o oMetaElement.o oPageLinkElement.o oSpanElement.o oAnchorElement.o oCoreAttributes.o oi18nAttributes.o oLinkAttributes.o oascii.o oconstants.o ofunctions.o otext.o
cmpp: cmpp.o fopensearch.o ogetoptv.o oputoptv.o oversion.o oerror.o omacro.o oscantext.o ochrtbl.o ochrupr.o ochrlwr.o ocursor.o opathspec.o ofindspec.o ofilespec.o ofileopen.o ofindfile.o owildcard.o ocontext.o osymbol.o oqueue.o oflagword.o oascii.o otext.o
csstidy: csstidy.o ogetoptv.o oputoptv.o oversion.o oerror.o oflagword.o ofileopen.o ofilespec.o ocontext.o owildcard.o oescape.o opathspec.o ocollect.o oascii.o oindent.o oprogram.o otext.o
ctokens: ctokens.o ogetoptv.o oputoptv.o oversion.o oerror.o oflagword.o okeywords.o oscantext.o ochrtbl.o ochrlwr.o ochrupr.o ocursor.o ocprocwords.o ocpluswords.o oclangwords.o oscancode.o oascii.o oconstants.o ofunctions.o otext.o
ctidy: ctidy.o ogetoptv.o oputoptv.o oversion.o ofileopen.o ofilespec.o ocontext.o owildcard.o oescape.o oerror.o opathspec.o ocollect.o ocgotowords.o ocexitwords.o okeywords.o oascii.o oindent.o octidy.o oinclude.o ocomment.o oflagword.o otext.o
cdep2: cdep2.o ogetoptv.o oputoptv.o oversion.o oerror.o oflagword.o oscantext.o ocursor.o ochrtbl.o ochrupr.o ochrlwr.o ocursor.o ofilespec.o ocontext.o opathspec.o owildcard.o oqueue.o odepend.o oascii.o otext.o
dnstidy: dnstidy.o ogetoptv.o oputoptv.o oversion.o oerror.o oflagword.o ofileopen.o ofilespec.o ocontext.o owildcard.o oescape.o opathspec.o ocollect.o oascii.o oindent.o otext.o
htmltidy: htmltidy.o ogetoptv.o oputoptv.o oversion.o oerror.o ofileopen.o ofilespec.o ocontext.o owildcard.o oescape.o opathspec.o ohtmltidy.o ocollect.o oindent.o oflagword.o okeywords.o oHTMLEmpty.o oascii.o  otext.o
index: index.o ogetoptv.o oputoptv.o oversion.o oerror.o oitem.o olist.o opathspec.o ofindspec.o owildcard.o ocontext.o oHTMLIndex.o oattribute.o owebpage.o oindent.o oenviron.o oPageLinkElement.o oSpanElement.o oAnchorElement.o oCoreAttributes.o oi18nAttributes.o oLinkAttributes.o oMetaElement.o otext.o
javatidy: javatidy.o ogetoptv.o oputoptv.o oversion.o oerror.o oflagword.o ofileopen.o ofilespec.o ocontext.o owildcard.o oescape.o opathspec.o ocollect.o oascii.o oindent.o oprogram.o otext.o
mmf2: mmf2.o ogetoptv.o oputoptv.o oversion.o ofilespec.o ocontext.o opathspec.o owildcard.o olist.o oitem.o omakefile.o oerror.o oscantext.o ocursor.o ocursor.o ochrtbl.o ochrupr.o ochrlwr.o osection.o oflagword.o oascii.o otext.o
mptidy: mptidy.o ogetoptv.o oputoptv.o oversion.o oflagword.o ofileopen.o ofilespec.o ocontext.o owildcard.o oescape.o oerror.o opathspec.o oprofile.o oswitch.o okeywords.o oascii.o ocollect.o omptidy.o otext.o
order2: order2.o ogetoptv.o oputoptv.o oversion.o oerror.o ograph.o oedges.o onodes.o oedge.o onode.o oflagword.o oascii.o otext.o
page: page.o ogetoptv.o oputoptv.o oversion.o opage.o otext.o
relate2: relate2.o ogetoptv.o oputoptv.o oversion.o oerror.o oflagword.o odepend.o oqueue.o opathspec.o owildcard.o oascii.o otext.o
sqltidy: sqltidy.o ogetoptv.o oputoptv.o oversion.o oerror.o oflagword.o ofileopen.o ofilespec.o ocontext.o owildcard.o oescape.o opathspec.o ocollect.o oascii.o oindent.o otext.o
defix: defix.o ogetoptv.o oputoptv.o oversion.o ocontext.o otext.o
syslog2: syslog2.o ogetoptv.o oputoptv.o oversion.o osyslog.o osyslogspec.o oerror.o
tokens: tokens.o ogetoptv.o oputoptv.o oversion.o oerror.o oflagword.o oscantext.o ochrtbl.o ochrlwr.o ochrupr.o ocursor.o oascii.o otext.o
pkg: pkg.o ogetoptv.o oputoptv.o oversion.o opackage.o oflagword.o otext.o
phptidy: phptidy.o ogetoptv.o oputoptv.o oversion.o ofileopen.o ofilespec.o ocontext.o owildcard.o oescape.o oerror.o opathspec.o ocollect.o ophptidy.o oascii.o oindent.o oflagword.o otext.o
profile: profile.o ogetoptv.o oputoptv.o oversion.o oprofile.o oswitch.o oerror.o oascii.o otext.o

# ====================================================================
# 
# --------------------------------------------------------------------

#include ../programs/programs.mak
#include ../classes/classes.mak

