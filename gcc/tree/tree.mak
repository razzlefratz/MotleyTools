# ====================================================================
# tree source files;
# --------------------------------------------------------------------

depend.o: depend.c tools.h link.h tree.h depend.h
dict.o: dict.c dictdefine.c dictlookup.c dictrevert.c dictreport.c
dictdefine.o: dictdefine.c tools.h dict.h tree.h link.h
dictlookup.o: dictlookup.c dict.h tree.h link.h
dictreport.o: dictreport.c tree.h dict.h link.h
dictrevert.o: dictrevert.c dict.h tree.h link.h
editnode.o: editnode.c tree.h
eventree.o: eventree.c tree.h
findnode.o: findnode.c tree.h
freenode.o: freenode.c tree.h
inorder.o: inorder.c tree.h
makenode.o: makenode.c tree.h tools.h
pathsort.o: pathsort.c memory.h types.h tree.h
postorder.o: postorder.c tree.h
preorder.o: preorder.c tree.h
savenode.o: savenode.c tree.h
term.o: term.c termdefine.c termlookup.c termreport.c
termdefine.o: termdefine.c tree.h memory.h
termlookup.o: termlookup.c tree.h tools.h
termreport.o: termreport.c tree.h tools.h
treesize.o: treesize.c tree.h
edge.o: edge.c types.h sizes.h memory.h edge.h

# ====================================================================
# files;
# --------------------------------------------------------------------

tree.h: types.h
	touch ../tree/${@}
depend.h: link.h tree.h
	touch ../tree/${@}
dict.h edge.h: tree.h
	touch ../tree/${@}

