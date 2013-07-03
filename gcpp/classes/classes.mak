# ====================================================================
# 
# --------------------------------------------------------------------

oagenda.o: oagenda.cpp oagenda.hpp
oattribute.o: oattribute.cpp oattribute.hpp
obuffer.o: obuffer.cpp obuffer.hpp
ocatalog.o: ocatalog.cpp ocatalog.hpp
oblock.o: oblock.cpp oblock.hpp ocollect.hpp
ochrclass.o: ochrclass.cpp ochrclass.hpp
ochrhex.o: ochrhex.cpp ochrhex.hpp
ochrlwr.o: ochrlwr.cpp chrlib.h strlib.h ochrlwr.hpp
ochroct.o: ochroct.cpp ochroct.hpp
ochrtable.o: ochrtable.cpp chrlib.h strlib.h ochrtable.hpp
ochrtbl.o: ochrtbl.cpp ochrtbl.hpp
ochrupr.o: ochrupr.cpp strlib.h chrlib.h ochrupr.hpp
ocode.o: ocode.cpp ocode.hpp
ocomment.o: ocomment.cpp ocomment.hpp oascii.hpp
ocontext.o: ocontext.cpp ocontext.hpp
ocursor.o: ocursor.cpp ocursor.hpp
odepend.o: odepend.cpp odepend.hpp
odocument.o: odocument.cpp odocument.hpp
oedge.o: oedge.cpp oedge.hpp
oedges.o: oedges.cpp oedges.hpp
osession.o: osession.cpp osession.hpp
oescape.o: oescape.cpp chrlib.h oescape.hpp
ofindfile.o: ofindfile.cpp ofindfile.hpp files.h
ofindspec.o: ofindspec.cpp ofindspec.hpp files.h find.h
ofileset.o: ofileset.cpp ofileset.hpp files.h
ofileopen.o: ofileopen.cpp ofileopen.hpp files.h
ofilespec.o: ofilespec.cpp ofilespec.hpp files.h
oflagword.o: oflagword.cpp oflagword.hpp
ogetoptv.o: ogetoptv.cpp ogetoptv.hpp oputoptv.hpp oversion.hpp
oglossary.o: oglossary.cpp oglossary.hpp
ograph.o: ograph.cpp ograph.hpp
ohexencode.o: ohexencode.cpp ohexencode.hpp
ohexencoder.o: ohexencoder.cpp chrlib.h ohexencoder.hpp
oheap.o: oheap.cpp oheap.hpp tools.h
ohtml.o: ohtml.cpp ohtml.hpp omarkup.hpp oascii.hpp otext.hpp
oindent.o: oindent.cpp oindent.hpp
oindex.o: oindex.cpp oindex.hpp
oitem.o: oitem.cpp oitem.hpp
okeep.o: okeep.cpp okeep.hpp
okeyword.o: okeyword.cpp okeyword.hpp
olist.o: olist.cpp tools.h olist.hpp
omarkup.o: omarkup.cpp omarkup.hpp 
onode.o: onode.cpp onode.hpp
onodes.o: onodes.cpp onodes.hpp
opathspec.o: opathspec.cpp opathspec.hpp files.h
ooctencode.o: ooctencode.cpp ooctencode.hpp
ooctencoder.o: ooctencoder.cpp chrlib.h ooctencoder.hpp
oscantext.o: oscantext.cpp oscantext.hpp ocursor.hpp ochrclass.hpp ochrlwr.hpp ochrupr.hpp tools.h
osection.o: osection.cpp osection.hpp
oSHA256.o: oSHA256.cpp oSHA256.hpp
ostrlib.o: ostrlib.cpp ostrlib.hpp
owildcard.o: owildcard.cpp owildcard.hpp
oxml.o: oxml.cpp oxml.hpp omarkup.hpp oascii.hpp otext.hpp
ocomment.o: ocomment.cpp ocomment.hpp oascii.hpp stdafx.hpp
ochtml.o: ochtml.cpp ochtml.hpp oscancode.hpp stdafx.hpp
ocinclude.o: ocinclude.cpp ocinclude.hpp flags.h stdafx.hpp
octidy.o: octidy.cpp octidy.hpp obuffer.hpp oinclude.hpp 
oclangwords.o: oclangwords.cpp strlib.h oclangwords.hpp
ocpluswords.o: ocpluswords.cpp ocpluswords.hpp okeyword.hpp stdafx.hpp
ocprocwords.o: ocprocwords.cpp ocprocwords.hpp okeyword.hpp stdafx.hpp
oscancode.o: oscancode.cpp oscancode.hpp okeyword.hpp stdafx.hpp
ocgotowords.o: ocgotowords.cpp ocgotowords.hpp okeyword.hpp stdafx.hpp
oconstants.o: oconstants.cpp oconstants.hpp okeyword.hpp stdafx.hpp
ofunctions.o: ofunctions.cpp ofunctions.hpp okeyword.hpp stdafx.hpp
oSHA256.o: oSHA256.cpp oSHA256.hpp
oHPAVKey.o: oHPAVKey.cpp oHPAVKey.hpp oflagword.hpp
oISOGlyph.o: oISOGlyph.cpp oISOGlyph.hpp
oHTMLIndex.o: oHTMLIndex.cpp files.h oHTMLIndex.hpp
oAnchorElement.o: oAnchorElement.cpp oAnchorElement.hpp
oCoreAttributes.o: oCoreAttributes.cpp oCoreAttributes.hpp
oHTMLAttribute.o: oHTMLAttribute.cpp strlib.h oHTMLAttribute.hpp
oHTMLElement.o: oHTMLElement.cpp strlib.h oHTMLElement.hpp
oLinkAttributes.o: oLinkAttributes.cpp oLinkAttributes.hpp
oMetaElement.o: oMetaElement.cpp oMetaElement.hpp
oPageLinkElement.o: oPageLinkElement.cpp oPageLinkElement.hpp
oSpanElement.o: oSpanElement.cpp oSpanElement.hpp
oi18nAttributes.o: oi18nAttributes.cpp oi18nAttributes.hpp
owebpage.o: owebpage.cpp owebpage.hpp
ohtmlempty.o: ohtmlempty.cpp ohtmlempty.hpp okeyword.hpp

# ====================================================================
# clang header files;
# --------------------------------------------------------------------

oagenda.hpp: oheap.hpp stdafx.hpp
oascii.hpp: stdafx.hpp
oattribute.hpp: otext.hpp stdafx.hpp
obreak.hpp: stdafx.hpp
obuffer.hpp: stdafx.hpp
ocalendar.hpp: oindent.hpp omonth.hpp stdafx.hpp
ocatalog.hpp: olist.hpp stdafx.hpp
ocblock.hpp: ocollect.hpp stdafx.hpp
ocgotowords.hpp: okeywords.hpp stdafx.hpp
ochannel.hpp: oethernet.hpp oflagword.hpp ointerface.hpp stdafx.hpp
ochrhex.hpp: stdafx.hpp
ochrlwr.hpp: ochrtbl.hpp stdafx.hpp
ochroct.hpp: stdafx.hpp
ochrtable.hpp: ochrtbl.hpp stdafx.hpp
ochrtbl.hpp: stdafx.hpp
ochrupr.hpp: ochrtbl.hpp stdafx.hpp
ochtml.hpp: oAnchorElement.hpp oISOGlyph.hpp oSpanElement.hpp ocprocwords.hpp ofilespec.hpp ofunctions.hpp oglossary.hpp oscancode.hpp owebpage.hpp
oclangwords.hpp: okeywords.hpp stdafx.hpp
oclibwords.hpp: okeywords.hpp stdafx.hpp
ocmassocindex.hpp: ofilespec.hpp otext.hpp owebpage.hpp
ocode.hpp: stdafx.hpp types.h
ocollect.hpp: stdafx.hpp
ocombine.hpp: stdafx.hpp
ocomment.hpp: oflagword.hpp otext.hpp stdafx.hpp
oconstants.hpp: okeywords.hpp stdafx.hpp
ocontext.hpp: stdafx.hpp
ocpluswords.hpp: okeywords.hpp stdafx.hpp
ocprocwords.hpp: okeywords.hpp stdafx.hpp
octidy.hpp: ocgotowords.hpp ocollect.hpp ocomment.hpp oinclude.hpp oindent.hpp stdafx.hpp
octype.hpp: stdafx.hpp
ocursor.hpp: stdafx.hpp
odate.hpp: oindex.hpp stdafx.hpp
odepend.hpp: oascii.hpp opathspec.hpp oqueue.hpp stdafx.hpp
odict.hpp: oqueue.hpp stdafx.hpp
odiscard.hpp: stdafx.hpp
odocument.hpp: otree.hpp stdafx.hpp
oedge.hpp: onode.hpp stdafx.hpp
oedges.hpp: oedge.hpp stdafx.hpp
oelement.hpp: otext.hpp stdafx.hpp
oenclose.hpp: ocollect.hpp stdafx.hpp
osession.hpp: stdafx.hpp
oerror.hpp: stdafx.hpp types.h
oescape.hpp: oascii.hpp stdafx.hpp
oethernet.hpp: stdafx.hpp
ofileopen.hpp: oerror.hpp ofilespec.hpp stdafx.hpp
ofileset.hpp: ocontext.hpp otext.hpp stdafx.hpp
ofilespec.hpp: ocontext.hpp stdafx.hpp
ofindfile.hpp: stdafx.hpp
ofindspec.hpp: oerror.hpp opathspec.hpp stdafx.hpp
oflagword.hpp: stdafx.hpp
oformat.hpp: stdafx.hpp
ofunctions.hpp: okeywords.hpp stdafx.hpp
ogetopt.hpp: stdafx.hpp
ogetoptv.hpp: oputoptv.hpp oversion.hpp
oglossary.hpp: oitem.hpp olist.hpp
ograph.hpp: oascii.hpp oedges.hpp oflagword.hpp onodes.hpp oqueue.hpp otext.hpp stdafx.hpp
oheap.hpp: oitem.hpp
ohexencode.hpp: stdafx.hpp
ohexencoder.hpp: oascii.hpp ochrupr.hpp stdafx.hpp
ohtmltidy.hpp: oHTMLEmptyElements.hpp ocollect.hpp oflagword.hpp oindent.hpp otext.hpp
oi18nAttributes.hpp: oattribute.hpp otext.hpp stdafx.hpp
oif.hpp: stdafx.hpp
oifs.hpp: oif.hpp stdafx.hpp
oinclude.hpp: otext.hpp stdafx.hpp types.h
oindent.hpp: stdafx.hpp
oindex.hpp: stdafx.hpp
ointerface.hpp: stdafx.hpp
ointerfaces.hpp: ointerface.hpp stdafx.hpp
oitem.hpp: otext.hpp stdafx.hpp
okeep.hpp: stdafx.hpp
okeywords.hpp: stdafx.hpp
olist.hpp: oitem.hpp
omacro.hpp: oflagword.hpp oscantext.hpp osymbol.hpp stdafx.hpp
omakefile.hpp: ofilespec.hpp oflagword.hpp oitem.hpp olist.hpp oscantext.hpp osection.hpp otext.hpp stdafx.hpp
omemory.hpp: stdafx.hpp
omonth.hpp: odate.hpp oindent.hpp stdafx.hpp
onode.hpp: otext.hpp stdafx.hpp
onodes.hpp: onode.hpp stdafx.hpp
onumber.hpp: stdafx.hpp types.h
ooctencode.hpp: stdafx.hpp
ooctencoder.hpp: stdafx.hpp
ooutline.hpp: otree.hpp stdafx.hpp
opackage.hpp: stdafx.hpp
opage.hpp: otext.hpp stdafx.hpp
opassword.hpp: stdafx.hpp
opathspec.hpp: owildcard.hpp stdafx.hpp
opcap.hpp: stdafx.hpp
ophptidy.hpp: ocollect.hpp oindent.hpp stdafx.hpp
oprefix.hpp: stdafx.hpp
oprofile.hpp: oswitch.hpp stdafx.hpp
oprogram.hpp: ocollect.hpp oindent.hpp stdafx.hpp
oputopt.hpp: stdafx.hpp
oputoptv.hpp: stdafx.hpp
oqueue.hpp: stdafx.hpp
oregex.hpp: oascii.hpp oescape.hpp stdafx.hpp
oroster.hpp: olist.hpp stdafx.hpp
oscancode.hpp: oclangwords.hpp oclibwords.hpp oconstants.hpp ocpluswords.hpp ocprocwords.hpp ofunctions.hpp oscantext.hpp stdafx.hpp
oscanfile.hpp: oascii.hpp ochrlwr.hpp ochrupr.hpp ocursor.hpp stdafx.hpp
oscantext.hpp: oascii.hpp ochrlwr.hpp ochrupr.hpp ocursor.hpp stdafx.hpp
osection.hpp: stdafx.hpp
osorter.hpp: stdafx.hpp
ostring.hpp: ochrlwr.hpp ochrupr.hpp stdafx.hpp
osuffix.hpp: stdafx.hpp
oswitch.hpp: stdafx.hpp
osymbol.hpp: oqueue.hpp otext.hpp stdafx.hpp
osyslog.hpp: stdafx.hpp syslog.h types.h
osyslogspec.hpp: oerror.hpp stdafx.hpp types.h
otabrule.hpp: stdafx.hpp
otext.hpp: stdafx.hpp
othread.hpp: otext.hpp stdafx.hpp
otodo.hpp: oitem.hpp stdafx.hpp
otree.hpp: stdafx.hpp
otruth.hpp: ocode.hpp stdafx.hpp
oversion.hpp: stdafx.hpp
owebpage.hpp: oMetaElement.hpp oPageLinkElement.hpp osession.hpp oindent.hpp otext.hpp stdafx.hpp
owildcard.hpp: stdafx.hpp
oxyz.hpp: stdafx.hpp

