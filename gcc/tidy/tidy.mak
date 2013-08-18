# ====================================================================
# files;
# --------------------------------------------------------------------

advance.o: advance.c tidy.h 
collect.o: collect.c tidy.h 
connect.o: collect.c tidy.h 
comment.o: comment.c tidy.h 
mention.o: mention.c tidy.h 
literal.o: literal.c tidy.h 
compact.o: compact.c tidy.h chars.h
content-css.o: content-css.c tidy.h content.c
content.o: content.c tidy.h
context-css.o: context-css.c tidy.h context.c chrlib.h types.h chars.h
context.o: context.c tidy.h chrlib.h types.h chars.h
discard.o: discard.c tidy.h tools.h types.h sizes.h
divider.o: divider.c tidy.h chars.h
endline.o: endline.c tidy.h
escaped.o: escaped.c tidy.h tools.h types.h sizes.h
fortran.o: fortran.c tidy.h chrlib.h types.h chars.h
newline.o: newline.c tidy.h
nmtoken.o: nmtoken.c tidy.h
consume.o: consume.c tidy.h 
noliteral.o: noliteral.c tidy.h chars.h
nocontext.o: nocontext.c tidy.h chars.h
nocomment.o: nocomment.c tidy.h chars.h
span.o: span.c tidy.h 
keep.o: keep.c tidy.h 
find.o: find.c tidy.h 

# ====================================================================
# files;
# --------------------------------------------------------------------

tidy.h:
	touch ../tidy/${@}

