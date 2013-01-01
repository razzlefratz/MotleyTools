# file: node/node.mak

# ====================================================================
# tree source files;
# --------------------------------------------------------------------

_xmlattribute.o: _xmlattribute.c nodes.h
_xmlvalue.o: _xmlvalue.c nodes.h
htmlscan.o: htmlscan.c chars.h error.h nodes.h strlib.h
nodes.o: nodes.c nodes.h
nodesize.o: nodesize.c nodes.h
reorder.o: reorder.c nodes.h
xmlattribute.o: xmlattribute.c nodes.h
xmlcontent.o: xmlcontent.c nodes.h
xmledit.o: xmledit.c error.h memory.h nodes.h number.h
xmlelement.o: xmlelement.c nodes.h
xmlfree.o: xmlfree.c nodes.h
xmlindent.o: xmlindent.c error.h nodes.h
xmlnode.o: xmlnode.c memory.h nodes.h
xmlopen.o: xmlopen.c error.h files.h memory.h nodes.h
xmlread.o: xmlread.c error.h files.h memory.h nodes.h
xmlsample.o: xmlsample.c format.h markup.h nodes.h
xmlscan.o: xmlscan.c chars.h error.h nodes.h strlib.h
xmlschema.o: xmlschema.c format.h markup.h nodes.h
xmlselect.o: xmlselect.c nodes.h
xmlstream.o: xmlstream.c error.h nodes.h
xmltree.o: xmltree.c format.h nodes.h
xmlvalue.o: xmlvalue.c nodes.h

# ====================================================================
# files;
# --------------------------------------------------------------------

node.h: 
	touch ../node/${@}

