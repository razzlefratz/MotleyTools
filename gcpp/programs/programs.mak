# file: programs/programs.mak

# ====================================================================
# 
# --------------------------------------------------------------------

calend2.o: calend2.cpp ogetoptv.hpp oputoptv.hpp ocalendar.hpp
call2.o: call2.cpp ogetoptv.hpp oputoptv.hpp oascii.hpp ocpluswords.hpp okeywords.hpp oflagword.hpp ofileopen.hpp opathspec.hpp ospan.hpp 
cblock2.o: cblock2.cpp stdafx.hpp ogetoptv.hpp ocontext.hpp owildcard.hpp ofileopen.hpp ofilespec.hpp opathspec.hpp ocgotowords.hpp oescape.hpp oindent.hpp oinclude.hpp ocollect.hpp ocblock.hpp 
chtml.o: chtml.cpp flags.h strlib.h ogetoptv.hpp oputoptv.hpp oversion.hpp ochtml.hpp
cmpp.o: cmpp.cpp ogetopt.hpp oputopt.hpp oerror.hpp oscantext.hpp omacro.hpp ofilespec.hpp ofindfile.hpp charset.h strlib.h
csstidy.o: csstidy.cpp ogetoptv.hpp oputoptv.hpp oversion.hpp oerror.hpp opathspec.hpp otidy.hpp tools.h flags.h
ctidy.o: ctidy.cpp ogetoptv.hpp oputoptv.hpp oversion.hpp oerror.hpp opathspec.hpp otidy.hpp tools.h flags.h
cfm.o: cfm.cpp ogetoptv.hpp oputoptv.hpp oversion.hpp oerror.hpp opathspec.hpp octidy.hpp tools.h flags.h
ctokens.o: ctokens.cpp ogetoptv.hpp oputoptv.hpp oscancode.hpp flags.h 
defix.o: defix.cpp ogetopt.hpp oputopt.hpp ocontext.hpp
cdep2.o: cdep2.cpp ogetoptv.hpp oputoptv.hpp oversion.hpp oerror.hpp ofilespec.hpp opathspec.hpp oqueue.hpp odepend.hpp oscantext.hpp tools.h flags.h
dnstidy.o: dnstidy.cpp ogetoptv.hpp oputoptv.hpp oversion.hpp oerror.hpp opathspec.hpp otidy.hpp tools.h flags.h
htmltidy.o: htmltidy.cpp ogetoptv.hpp oputoptv.hpp oversion.hpp oerror.hpp opathspec.hpp otidy.hpp tools.h flags.h
index.o: index.cpp ogetoptv.hpp oputoptv.hpp oversion.hpp oHTMLIndex.hpp ofilespec.hpp tools.h flags.h
javatidy.o: javatidy.cpp ogetoptv.hpp oputoptv.hpp oversion.hpp oerror.hpp opathspec.hpp otidy.hpp tools.h flags.h
mmf2.o: mmf2.cpp ogetoptv.hpp oputoptv.hpp oversion.hpp omakefile.hpp tools.h flags.h types.h
order2.o: order2.cpp ogetoptv.hpp oputoptv.hpp oversion.hpp ograph.hpp tools.h types.h flags.h sizes.h 
page.o: page.cpp ogetoptv.hpp oputoptv.hpp oversion.hpp
phptidy.o: phptidy.cpp ogetoptv.hpp oputoptv.hpp oversion.hpp oerror.hpp opathspec.hpp otidy.hpp tools.h flags.h
pkg.o: pkg.cpp ogetoptv.hpp oputopt.hpp oversion.hpp opackage.hpp tools.h flags.h types.h
profile.o: profile.cpp ogetoptv.hpp oputopt.hpp oversion.hpp oprofile.hpp tools.h flags.h
relate2.o: relate2.cpp ogetoptv.hpp oputoptv.hpp odepend.hpp 
sqltidy.o: sqltidy.cpp ogetoptv.hpp oputoptv.hpp oversion.hpp oerror.hpp opathspec.hpp otidy.hpp tools.h flags.h
syslog2.o: syslog2.cpp ogetoptv.hpp oputoptv.hpp oversion.hpp osyslog.hpp oerror.hpp flags.h files.h
tokens.o: tokens.cpp ogetoptv.hpp oputoptv.hpp oscantext.hpp flags.h

