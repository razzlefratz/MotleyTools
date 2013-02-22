# ====================================================================
# source files;
# --------------------------------------------------------------------

alert.o: alert.c error.h types.h
arith.o: arith.c number.h tools.h types.h sizes.h
argv2str.o: argv2str.c
atoin.o: atoin.c number.h tools.h types.h sizes.h
b64dump.o: b64dump.c base64.h types.h
b64decode.o: b64decode.c memory.h
b64encode.o: b64encode.c memory.h
bindecode.o: bindecode.c number.h memory.h tools.h types.h sizes.h
binout.o: binout.c number.h 
bytespec.o: bytespec.c memory.h number.h error.h
breakout.o: breakout.c format.h
cdigit.o: cdigit.c number.h tools.h types.h sizes.h
checksum16.o: checksum16.c memory.h
checksum32.o: checksum32.c memory.h
chkoptv.o: chkoptv.c getoptv.h putoptv.h
chrdcl.o: chrdcl.c dcl.h error.h memory.h tree.h emalloc.c types.h
chrout.o: chrout.c memory.h 
cgets.o: cgets.c tools.h
codeload.o: codeload.c symbol.h number.h error.h
codelist.o: codelist.c symbol.h
codename.o: codename.c symbol.h 
codesave.o: codesave.c tools.h types.h sizes.h
config.o: config.c config.h types.h
console.o: console.c tools.h
cread.o: cread.c tools.h types.h sizes.h
cwrite.o: cwrite.c tools.h types.h sizes.h
dataspec.o: dataspec.c memory.h number.h error.h
debug.o: debug.c types.h error.h
decdecode.o: decdecode.c types.h number.h tools.h sizes.h
decencode.o: decencode.c number.h tools.h types.h sizes.h
decout.o: decout.c number.h 
digit.o: digit.c number.h 
efopen.o: efopen.c tools.h error.h types.h sizes.h
efreopen.o: efreopen.c tools.h error.h types.h sizes.h
emalloc.o: emalloc.c tools.h error.h types.h sizes.h
endian.o: endian.c memory.h types.h
eperror.o: eperror.c tools.h types.h sizes.h
eprintf.o: eprintf.c tools.h types.h sizes.h
equate.o: equate.c number.h tools.h types.h sizes.h
erealloc.o: erealloc.c tools.h error.h types.h sizes.h
error.o: error.c types.h error.h
error_at_line.o: error_at_line.c types.h error.h
errors.o: errors.c types.h tools.h typename.c typesave.c sizes.h error.h
event.o: event.c error.h types.h
fdchecksum16.o: fdchecksum16.c memory.h
fdchecksum32.o: fdchecksum32.c memory.h
fdgetc.o: fdgetc.c
fgetline.o: fgetline.c tools.h types.h sizes.h
fgetlongline.o: fgetlongline.c tools.h types.h sizes.h
fgetshortline.o: fgetshortline.c tools.h types.h sizes.h
fgetv.o: fgetv.c tools.h types.h sizes.h
fprintm.o: fprintm.c number.h memory.h binout.c hexout.c decout.c tools.h types.h sizes.h
fprintv.o: fprintv.c tools.h types.h sizes.h
fputline.o: fputline.c tools.h types.h sizes.h
fputn.o: fputn.c tools.h number.h types.h sizes.h
fputv.o: fputv.c tools.h types.h sizes.h
fvalue.o: fvalue.c
getch.o: getch.c unget.h tools.h types.h sizes.h
getclass.o: getclass.c tools.h types.h sizes.h
getclass.demo.o: getclass.demo.c getclass.c tools.h types.h sizes.h
getopt.o: getopt.c error.h getopt.h version.h types.h
getopt1.o: getopt1.c
getargv.o: getargv.c chars.h symbol.h
getoptv.o: getoptv.c getoptv.h putoptv.h version.h
getst.o: getst.c unget.h
getvalue.o: getvalue.c tools.h types.h sizes.h
help.o: help.c linux.h types.h
hexdecode.o: hexdecode.c number.h memory.h tools.h types.h sizes.h
hexdump.o: hexdump.c memory.h number.h
hexencode.o: hexencode.c memory.h number.h tools.h types.h sizes.h
hexload.o: hexload.c number.h error.h types.h chars.h
hexoffset.o: hexoffset.c memory.h number.h 
hexout.o: hexout.c number.h tools.h types.h sizes.h
hexread.o: hexread.c memory.h error.h types.h
hexview.o: hexdump.c memory.h number.h 
hostspec.o: hostspec.c tools.h sizes.h strlib.h types.h
ietfdecode.o: ietfdecode.c number.h memory.h tools.h types.h sizes.h
ietfencode.o: ietfencode.c number.h memory.h tools.h types.h sizes.h
indent.o: indent.c format.h
ipv4spec.o: ipv4spec.c tools.h number.h error.h types.h
ipv6spec.o: ipv6spec.c tools.h number.h error.h types.h
itoan.o: itoan.c number.h tools.h types.h sizes.h
itoax.o: itoax.c number.h tools.h types.h sizes.h
itosm.o: itosm.c number.h tools.h types.h sizes.h
itosn.o: itosn.c number.h tools.h types.h sizes.h
memdecr.o: memdecr.c memory.h
memincr.o: memincr.c memory.h
memout.o: memout.c memory.h 
memfold.o: memswap.c memory.h 
memswap.o: memswap.c memory.h
memwrap.o: memwrap.c memory.h
modespec.o: modespec.c tools.h error.h chars.h types.h sizes.h
more.o: more.c
namecode.o: namecode.c types.h tools.h sizes.h
nametype.o: nametype.c types.h tools.h sizes.h
nodef.o: nodef.c symbol.h types.h chars.h 
number.o: number.c tools.h types.h sizes.h
oui.o: oui.c tools.h typename.c types.h sizes.h
output.o: output.c format.h
page.o: page.c page.h tools.h date.h 
printb.o: printb.c number.h tools.h types.h sizes.h
printd.o: printd.c number.h tools.h types.h sizes.h
printn.o: printn.c number.h tools.h types.h sizes.h
printv.o: printv.c tools.h types.h sizes.h
printx.o: printx.c number.h memory.h tools.h types.h sizes.h
profile.o: profile.c tools.h chars.h number.h types.h sizes.h
putopt.o: putopt.c getopt.h putopt.h
putoptv.o: putoptv.c getoptv.h putoptv.h
readtoken.o: readtoken.c tools.h types.h sizes.h
serial.o: serial.c number.h tools.h types.h sizes.h
setinfo.o: setinfo.c info.h version.h strlib.h linux.h date.h sizes.h types.h
signf.o: signf.c tools.h types.h sizes.h
sintspec.o: sintspec.c tools.h types.h sizes.h
sockspec.o: sockspec.c tools.h sizes.h types.h
statement.o: statement.c tools.h types.h sizes.h
strdcl.o: strdcl.c dcl.h memory.h error.h tree.h error.c emalloc.c types.h
symbol.o: symbol.c number.h tools.h types.h sizes.h
synonym.o: synonym.c symbol.h types.h
synonyms.o: synonyms.c symbol.h types.h
tabrule.o: tabrule.c tabs.h tools.h types.h sizes.h
tabs.o: tabs.c tools.h tabs.h types.h sizes.h tools.h
tabspec.o: tabspec.c tabs.h tools.h types.h sizes.h
termspec.o: termspec.c symbol.h types.h error.h 
trace.o: trace.c
truth.o: truth.c number.h tools.h types.h sizes.h
typeload.o: typeload.c symbol.h number.h error.h
typelist.o: typelist.c symbol.h
typename.o: typename.c symbol.h 
typesave.o: typesave.c tools.h error.h format.h markup.h 
basespec.c.o: basespec.c.c number.h error.h
uintspec.o: uintspec.c number.h error.h tools.h types.h sizes.h
unixdecode.o: unixdecode.c chrlib.h number.h types.h chars.h tools.h sizes.h
unixencode.o: unixencode.c number.h tools.h types.h sizes.h
version.o: version.c version.h
waitspec.o: waitspec.c tools.h types.h sizes.h

# ====================================================================
# header files;
# --------------------------------------------------------------------

cmassoc.h: console.h files.h chars.h error.h flags.h getoptv.h memory.h number.h paths.h putoptv.h sizes.h symbol.h tools.h types.h version.h vtdef.h
console.h: getoptv.h putoptv.h version.h error.h
chars.h flags.h getoptv.h number.h paths.h putoptv.h sizes.h types.h version.h vtdef.h:
markup.h: version.h
symbol.h: chars.h sizes.h types.h
tools.h error.h memory.h: types.h
tabs.h: tools.h types.h
info.h: sizes.h date.h


codename.o: codename.c tools.h types.h
typename.o: typename.c tools.h types.h


