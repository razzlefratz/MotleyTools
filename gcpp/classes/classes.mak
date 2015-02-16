oAnchorElement.o: oAnchorElement.cpp oAnchorElement.hpp
oCoreAttributes.o: oCoreAttributes.cpp oCoreAttributes.hpp
oEthernet.hpp: oEthernetAddress.hpp
oEthernet.o: oEthernet.cpp oEthernet.hpp omemory.hpp
oEthernetAddress.hpp: omemory.hpp
oEthernetAddress.o: oEthernetAddress.cpp oEthernetAddress.hpp
oHPAVKey.o: oHPAVKey.cpp oHPAVKey.hpp oflagword.hpp
oHTMLAttribute.o: oHTMLAttribute.cpp strlib.h oHTMLAttribute.hpp
oHTMLElement.o: oHTMLElement.cpp strlib.h oHTMLElement.hpp
oHTMLIndex.o: oHTMLIndex.cpp files.h oHTMLIndex.hpp
oISOGlyph.o: oISOGlyph.cpp oISOGlyph.hpp
oInternet.hpp: oInternetAddress.hpp
oInternet.o: oInternet.cpp oEthernet.hpp oInternet.hpp oInternetAddress.hpp omemory.hpp
oInternetAddress.hpp: omemory.hpp
oInternetAddress.o: oInternetAddress.cpp oInternetAddress.hpp
oLinkAttributes.o: oLinkAttributes.cpp oLinkAttributes.hpp
oMetaElement.o: oMetaElement.cpp oMetaElement.hpp
oPageLinkElement.o: oPageLinkElement.cpp oPageLinkElement.hpp
oSHA256.o: oSHA256.cpp oSHA256.hpp
oSHA256.o: oSHA256.cpp oSHA256.hpp
oSpanElement.o: oSpanElement.cpp oSpanElement.hpp
oagenda.hpp: oheap.hpp stdafx.hpp
oagenda.o: oagenda.cpp oagenda.hpp
oascii.hpp: stdafx.hpp
oattribute.hpp: otext.hpp stdafx.hpp
oattribute.o: oattribute.cpp oattribute.hpp
oblock.o: oblock.cpp oblock.hpp ocollect.hpp
obreak.hpp: stdafx.hpp
obuffer.hpp: stdafx.hpp
obuffer.o: obuffer.cpp obuffer.hpp
ocalendar.hpp: oindent.hpp omonth.hpp stdafx.hpp
ocatalog.hpp: olist.hpp stdafx.hpp
ocatalog.o: ocatalog.cpp ocatalog.hpp
ocblock.hpp: ocollect.hpp stdafx.hpp
ocgotowords.hpp: okeywords.hpp stdafx.hpp
ocgotowords.o: ocgotowords.cpp ocgotowords.hpp okeyword.hpp stdafx.hpp
oconnetc.hpp: oethernet.hpp oflagword.hpp ointerface.hpp stdafx.hpp
ochrclass.o: ochrclass.cpp ochrclass.hpp
ochrhex.hpp: stdafx.hpp
ochrhex.o: ochrhex.cpp ochrhex.hpp
ochrlwr.hpp: ochrtbl.hpp stdafx.hpp
ochrlwr.o: ochrlwr.cpp chrlib.h strlib.h ochrlwr.hpp
ochroct.hpp: stdafx.hpp
ochroct.o: ochroct.cpp ochroct.hpp
ochrtable.hpp: ochrtbl.hpp stdafx.hpp
ochrtable.o: ochrtable.cpp chrlib.h strlib.h ochrtable.hpp
ochrtbl.hpp: stdafx.hpp
ochrtbl.o: ochrtbl.cpp ochrtbl.hpp
ochrupr.hpp: ochrtbl.hpp stdafx.hpp
ochrupr.o: ochrupr.cpp strlib.h chrlib.h ochrupr.hpp
ochtml.hpp: oAnchorElement.hpp oISOGlyph.hpp oSpanElement.hpp ocprocwords.hpp ofilespec.hpp ofunctions.hpp oglossary.hpp oscancode.hpp owebpage.hpp
ochtml.o: ochtml.cpp ochtml.hpp oscancode.hpp stdafx.hpp
ocinclude.o: ocinclude.cpp ocinclude.hpp flags.h stdafx.hpp
oclangwords.hpp: okeywords.hpp stdafx.hpp
oclangwords.o: oclangwords.cpp strlib.h oclangwords.hpp
oclibwords.hpp: okeywords.hpp stdafx.hpp
ocmassocindex.hpp: ofilespec.hpp otext.hpp owebpage.hpp
ocode.hpp: stdafx.hpp types.h
ocode.o: ocode.cpp ocode.hpp
ocollect.hpp: stdafx.hpp
ocombine.hpp: stdafx.hpp
ocomment.hpp: oflagword.hpp otext.hpp stdafx.hpp
ocomment.o: ocomment.cpp ocomment.hpp oascii.hpp
ocomment.o: ocomment.cpp ocomment.hpp oascii.hpp stdafx.hpp
oconstants.hpp: okeywords.hpp stdafx.hpp
oconstants.o: oconstants.cpp oconstants.hpp okeyword.hpp stdafx.hpp
ocontext.hpp: stdafx.hpp
ocontext.o: ocontext.cpp ocontext.hpp
ocpluswords.hpp: okeywords.hpp stdafx.hpp
ocpluswords.o: ocpluswords.cpp ocpluswords.hpp okeyword.hpp stdafx.hpp
ocprocwords.hpp: okeywords.hpp stdafx.hpp
ocprocwords.o: ocprocwords.cpp ocprocwords.hpp okeyword.hpp stdafx.hpp
octidy.hpp: ocgotowords.hpp ocollect.hpp ocomment.hpp oinclude.hpp oindent.hpp stdafx.hpp
octidy.o: octidy.cpp octidy.hpp obuffer.hpp oinclude.hpp 
octype.hpp: stdafx.hpp
ocursor.hpp: stdafx.hpp
ocursor.o: ocursor.cpp ocursor.hpp
odate.hpp: oindex.hpp stdafx.hpp
odepend.hpp: oascii.hpp opathspec.hpp oqueue.hpp stdafx.hpp
odepend.o: odepend.cpp odepend.hpp
odict.hpp: oqueue.hpp stdafx.hpp
odiscard.hpp: stdafx.hpp
odocument.hpp: otree.hpp stdafx.hpp
odocument.o: odocument.cpp odocument.hpp
oedge.hpp: onode.hpp stdafx.hpp
oedge.o: oedge.cpp oedge.hpp
oedges.hpp: oedge.hpp stdafx.hpp
oedges.o: oedges.cpp oedges.hpp
oelement.hpp: otext.hpp stdafx.hpp
oenclose.hpp: ocollect.hpp stdafx.hpp
oerror.hpp: stdafx.hpp types.h
oescape.hpp: oascii.hpp stdafx.hpp
oescape.o: oescape.cpp chrlib.h oescape.hpp
oEthernetHeader.hpp: stdafx.hpp
ofileopen.hpp: oerror.hpp ofilespec.hpp stdafx.hpp
ofileopen.o: ofileopen.cpp ofileopen.hpp files.h
ofileset.hpp: ocontext.hpp otext.hpp stdafx.hpp
ofileset.o: ofileset.cpp ofileset.hpp files.h
ofilespec.hpp: ocontext.hpp stdafx.hpp
ofilespec.o: ofilespec.cpp ofilespec.hpp files.h
ofindfile.hpp: stdafx.hpp
ofindfile.o: ofindfile.cpp ofindfile.hpp files.h
ofindspec.hpp: oerror.hpp opathspec.hpp stdafx.hpp
ofindspec.o: ofindspec.cpp ofindspec.hpp files.h find.h
oflagword.hpp: stdafx.hpp
oflagword.o: oflagword.cpp oflagword.hpp
oformat.hpp: stdafx.hpp
ofunctions.hpp: okeywords.hpp stdafx.hpp
ofunctions.o: ofunctions.cpp ofunctions.hpp okeyword.hpp stdafx.hpp
ogetoptv.hpp: oputoptv.hpp oversion.hpp
ogetoptv.o: ogetoptv.cpp ogetoptv.hpp oputoptv.hpp oversion.hpp
oglossary.hpp: oitem.hpp olist.hpp
oglossary.o: oglossary.cpp oglossary.hpp
ograph.hpp: oascii.hpp oedges.hpp oflagword.hpp onodes.hpp oqueue.hpp otext.hpp stdafx.hpp
ograph.o: ograph.cpp ograph.hpp
oheap.hpp: oitem.hpp
oheap.o: oheap.cpp oheap.hpp tools.h
ohexencode.hpp: stdafx.hpp
ohexencode.o: ohexencode.cpp ohexencode.hpp
ohexencoder.hpp: oascii.hpp ochrupr.hpp stdafx.hpp
ohexencoder.o: ohexencoder.cpp chrlib.h ohexencoder.hpp
ohtml.o: ohtml.cpp ohtml.hpp omarkup.hpp oascii.hpp otext.hpp
ohtmlempty.o: ohtmlempty.cpp ohtmlempty.hpp okeyword.hpp
ohtmltidy.hpp: oHTMLEmptyElements.hpp ocollect.hpp oflagword.hpp oindent.hpp otext.hpp
oi18nAttributes.hpp: oattribute.hpp otext.hpp stdafx.hpp
oi18nAttributes.o: oi18nAttributes.cpp oi18nAttributes.hpp
oif.hpp: stdafx.hpp
oifs.hpp: oif.hpp stdafx.hpp
oinclude.hpp: otext.hpp stdafx.hpp types.h
oindent.hpp: stdafx.hpp
oindent.o: oindent.cpp oindent.hpp
oindex.hpp: stdafx.hpp
oindex.o: oindex.cpp oindex.hpp
ointerface.hpp: stdafx.hpp
ointerfaces.hpp: ointerface.hpp stdafx.hpp
oitem.hpp: otext.hpp stdafx.hpp
oitem.o: oitem.cpp oitem.hpp
okeep.hpp: stdafx.hpp
okeep.o: okeep.cpp okeep.hpp
okeyword.o: okeyword.cpp okeyword.hpp
okeywords.hpp: stdafx.hpp
olist.hpp: oitem.hpp
olist.o: olist.cpp tools.h olist.hpp
omacro.hpp: oflagword.hpp oscantext.hpp osymbol.hpp stdafx.hpp
omakefile.hpp: ofilespec.hpp oflagword.hpp oitem.hpp olist.hpp oscantext.hpp osection.hpp otext.hpp stdafx.hpp
omarkup.o: omarkup.cpp omarkup.hpp 
omemory.hpp: stdafx.hpp
omonth.hpp: odate.hpp oindent.hpp stdafx.hpp
onode.hpp: otext.hpp stdafx.hpp
onode.o: onode.cpp onode.hpp
onodes.hpp: onode.hpp stdafx.hpp
onodes.o: onodes.cpp onodes.hpp
onumber.hpp: stdafx.hpp types.h
ooctencode.hpp: stdafx.hpp
ooctencode.o: ooctencode.cpp ooctencode.hpp
ooctencoder.hpp: stdafx.hpp
ooctencoder.o: ooctencoder.cpp chrlib.h ooctencoder.hpp
ooutline.hpp: otree.hpp stdafx.hpp
opackage.hpp: stdafx.hpp
opage.hpp: otext.hpp stdafx.hpp
opassword.hpp: stdafx.hpp
opathspec.hpp: owildcard.hpp stdafx.hpp
opathspec.o: opathspec.cpp opathspec.hpp files.h
opcap.hpp: stdafx.hpp
ophptidy.hpp: ocollect.hpp oindent.hpp stdafx.hpp
oprefix.hpp: stdafx.hpp
oprofile.hpp: oswitch.hpp stdafx.hpp
oprogram.hpp: ocollect.hpp oindent.hpp stdafx.hpp
oputoptv.hpp: stdafx.hpp
oqueue.hpp: stdafx.hpp
oregex.hpp: oascii.hpp oescape.hpp stdafx.hpp
oroster.hpp: olist.hpp stdafx.hpp
oscancode.hpp: oclangwords.hpp oclibwords.hpp oconstants.hpp ocpluswords.hpp ocprocwords.hpp ofunctions.hpp oscantext.hpp stdafx.hpp
oscancode.o: oscancode.cpp oscancode.hpp okeyword.hpp stdafx.hpp
oscanfile.hpp: oascii.hpp ochrlwr.hpp ochrupr.hpp ocursor.hpp stdafx.hpp
oscantext.hpp: oascii.hpp ochrlwr.hpp ochrupr.hpp ocursor.hpp stdafx.hpp
oscantext.o: oscantext.cpp oscantext.hpp ocursor.hpp ochrclass.hpp ochrlwr.hpp ochrupr.hpp tools.h
osection.hpp: stdafx.hpp
osection.o: osection.cpp osection.hpp
osession.hpp: stdafx.hpp
osession.o: osession.cpp osession.hpp
osorter.hpp: stdafx.hpp
ostring.hpp: ochrlwr.hpp ochrupr.hpp stdafx.hpp
ostrlib.o: ostrlib.cpp ostrlib.hpp
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
owebpage.o: owebpage.cpp owebpage.hpp
owildcard.hpp: stdafx.hpp
owildcard.o: owildcard.cpp owildcard.hpp
oxml.o: oxml.cpp oxml.hpp omarkup.hpp oascii.hpp otext.hpp
oxyz.hpp: stdafx.hpp
