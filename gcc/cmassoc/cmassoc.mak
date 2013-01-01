# file: cmassoc/cmassoc.mak

# ====================================================================
# programs;
# --------------------------------------------------------------------

_basic.o: _basic.c cmassoc.h efreopen.c error.c getoptv.c putoptv.c version.c
_main.o: _main.c
afm.o: afm.c ascii.h chrlib.h chrupr.c cmassoc.h emalloc.c error.c getoptv.c makepath.c mergepath.c putoptv.c splitpath.c strcomp.c strconv.c tabs.c tabs.h tabspec.c todigit.c uintspec.c version.c vfopen.c
align.o: align.c chrindex.c chrlib.h chruesc.c cmassoc.h error.c getoptv.c makepath.c mergepath.c putoptv.c splitpath.c strlib.h struesc.c todigit.c uintspec.c version.c vfopen.c
argv.o: argv.c
argvesc.o: argvesc.c chrindex.c chrlib.h chruesc.c strlib.h struesc.c todigit.c
auth.o: auth.c clang.h cmassoc.h efreopen.c error.c getoptv.c linux.h putoptv.c version.c
b64.o: b64.c base64.h cmassoc.h error.c error.h getoptv.c makepath.c mergepath.c putoptv.c splitpath.c todigit.c uintspec.c version.c vfopen.c
bang.o: bang.c clang.h cmassoc.h error.c files.h find.c getoptv.c linux.h makefind.c makepath.c mergepath.c partfile.c partpath.c putoptv.c splitpath.c version.c vfopen.c
bin2hex.o: bin2hex.c cmassoc.h efreopen.c error.c getoptv.c putoptv.c todigit.c uintspec.c version.c
blank.o: blank.c cmassoc.h console.c files.h makepath.c mergepath.c splitpath.c todigit.c uintspec.c vfopen.c
calend.o: calend.c cmassoc.h date.h dayofwk.c endofmo.c error.c getoptv.c isleap.c putoptv.c sintspec.c sv_date1.c sv_month.c version.c
call.o: call.c cmassoc.h console.c efreopen.c nocomment.c nocontext.c noescaped.c noliteral.c strlib.h svindex.c tidy.h
case.o: case.c chrlib.h chrlwr.c chrupr.c cmassoc.h error.c escaped.c getoptv.c keep.c literal.c makepath.c mergepath.c putoptv.c splitpath.c strcomp.c strconv.c strlib.h tidy.h version.c vfopen.c
cat.o: cat.c cmassoc.h efreopen.c error.c getoptv.c putoptv.c todigit.c uintspec.c version.c
catalog.o: catalog.c cmassoc.h emalloc.c error.c filepart.c format.h getoptv.c indent.c makepath.c markup.h mergepath.c putoptv.c splitpath.c todigit.c uintspec.c version.c vfopen.c
cblock.o: cblock.c capsule.c chars.h cmassoc.h comment.c content.c context.c control.c error.c escaped.c fortran.c getoptv.c keep.c literal.c makepath.c mergepath.c putoptv.c splitpath.c tidy.h version.c vfopen.c
cbrief.o: cbrief.c cmassoc.h console.c escaped.c keep.c literal.c makepath.c mergepath.c nocomment.c splitpath.c tidy.h vfopen.c
cdep.o: cdep.c cmassoc.h depend.c depend.h efopen.c emalloc.c erealloc.c error.c fgetline.c find.c fullpath.c getoptv.c havebreak.c havetoken.c isbreak.c istoken.c makepath.c mergepath.c nextbreak.c nexttoken.c partfile.c partpath.c putoptv.c scan.h scanalnum.c scanbreak.c scandigit.c scanflush.c scaninput.c scanspace.c scanstart.c scantoken.c scanuntil.c splitpath.c tokentext.c version.c
cedit.o: cedit.c cmassoc.h error.c getoptv.c makepath.c mergepath.c putoptv.c splitpath.c version.c vfopen.c
change.o: change.c charset.c chrindex.c chrlib.h chruesc.c chruescmap.c cmassoc.h emalloc.c error.c fgetline.c files.h getoptv.c makefind.c makepath.c match.c mergepath.c partfile.c partpath.c putoptv.c regex.h regexcomp.c regexfree.c regexhelp.c regexmake.c regexshow.c regexspan.c splitpath.c strlib.h struesc.c sv_ascii.c todigit.c version.c vfopen.c
checkmode.o: checkmode.c atoin.c cmassoc.h efopen.c error.c getoptv.c linux.h putoptv.c version.c
chkbld.o: chkbld.c cmassoc.h efreopen.c emalloc.c error.c fgetline.c files.h getoptv.c havebreak.c havetoken.c isbreak.c istoken.c nextbreak.c nexttoken.c putoptv.c scan.h scanalnum.c scandigit.c scanflush.c scaninput.c scanreset.c scanspace.c scantoken.c scanuntil.c tokentext.c version.c
chperm.o: chperm.c cmassoc.h error.c files.h find.c getoptv.c makefind.c makepath.c match.c mergepath.c modespec.c partfile.c partpath.c putoptv.c splitpath.c version.c
chr.o: chr.c chrlib.h cmassoc.h efreopen.c error.c getoptv.c putoptv.c sv_ascii.c version.c
cinc.o: cinc.c chrlib.h clang.h cmassoc.h efopen.c error.c getoptv.c makepath.c mergepath.c putoptv.c splitpath.c version.c
clear.o: clear.c cmassoc.h console.c
cmerge.o: cmerge.c clang.h cmassoc.h date.h efopen.c emalloc.c erealloc.c error.c getoptv.c getusername.c havebreak.c havetoken.c isbreak.c istoken.c linux.h list.h listappend.c listcreate.c listdelete.c listexpand.c listrubout.c makefind.c makepath.c mergepath.c nextbreak.c nexttoken.c partfile.c partpath.c putoptv.c scan.h scanalnum.c scandigit.c scanflush.c scaninput.c scanspace.c scanstart.c scantoken.c scanuntil.c splitpath.c tokentext.c version.c
cpp2c.o: cpp2c.c chrlib.h clang.h cmassoc.h error.c escaped.c fortran.c getoptv.c keep.c literal.c makepath.c mergepath.c putoptv.c splitpath.c tidy.h version.c vfopen.c
crlf.o: crlf.c cmassoc.h console.c files.h makepath.c mergepath.c splitpath.c vfopen.c
csv2html.o: csv2html.c cmassoc.h console.c efreopen.c filepart.c format.h indent.c markup.h todigit.c uintspec.c
ctar.o: ctar.c ccollect.c cinclude.c clang.h cmassoc.h emalloc.c erealloc.c error.c error_on_line.c fgetline.c havebreak.c havetoken.c isbreak.c istoken.c list.h listappend.c listcreate.c listexpand.c makepath.c mergepath.c nextbreak.c nexttoken.c partfile.c partpath.c scan.h scanalnum.c scanbreak.c scandigit.c scanflush.c scaninput.c scanreset.c scanspace.c scanstart.c scantoken.c scanuntil.c splitpath.c tokentext.c
define.o: define.c cmassoc.h console.c efreopen.c indent.c markup.h symbol.h todigit.c typeload.c typesave.c
defix.o: defix.c chruesc.c cmassoc.h console.c strlib.h struesc.c todigit.c
delta.o: delta.c cmassoc.h efreopen.c error.c error_on_line.c getoptv.c putoptv.c todigit.c uintspec.c version.c
detab.o: detab.c cmassoc.h emalloc.c error.c files.h getoptv.c makepath.c match.c mergepath.c putoptv.c splitpath.c tabs.c tabs.h tabspec.c version.c vfopen.c
detag.o: detag.c cmassoc.h console.c efreopen.c nocomment.c nocontent.c nocontext.c noescaped.c noliteral.c tidy.h todigit.c uintspec.c
dif.o: dif.c cmassoc.h efopen.c efreopen.c emalloc.c error.c getoptv.c link.h makeitem.c putoptv.c queue.c todigit.c uintspec.c version.c
dls.o: dls.c cmassoc.h console.c emalloc.c erealloc.c getviewport.c linux.h list.h listcolumn.c listcreate.c listdelete.c listdetect.c listexpand.c listinsert.c todigit.c uintspec.c
dmp2hex.o: dmp2hex.c cmassoc.h error.c getoptv.c putoptv.c version.c
ds.o: ds.c SHA256.h SHA256Block.c SHA256Fetch.c SHA256Ident.c SHA256Match.c SHA256Reset.c SHA256Write.c console.c efreopen.c error.h files.h getoptv.h sizes.h
dump.o: dump.c chrlib.h cmassoc.h console.c
efru.o: efru.c basespec.c channel.c channel.h closechannel.c error.c error.h flags.h getoptv.c getoptv.h hexdecode.c hexdump.c hexstring.c memory.h number.h openchannel.c putoptv.c putoptv.h readpacket.c sendpacket.c todigit.c types.h uintspec.c version.c
efsu.o: efsu.c basespec.c channel.c channel.h closechannel.c error.c error.h flags.h getoptv.c getoptv.h hexdump.c hexencode.c hexload.c memory.h number.h openchannel.c putoptv.c putoptv.h readpacket.c sendpacket.c symbol.h synonym.c todigit.c uintspec.c version.c
enbrace.o: enbrace.c cmassoc.h error.c getoptv.c makepath.c mergepath.c putoptv.c splitpath.c version.c vfopen.c
enfix.o: enfix.c chrlib.h chruesc.c cmassoc.h error.c getoptv.c makepath.c mergepath.c putoptv.c splitpath.c strlib.h struesc.c todigit.c version.c vfopen.c
englyph.o: englyph.c chrlib.h cmassoc.h efreopen.c emalloc.c error.c getoptv.c putoptv.c strfglyph.c strlib.h sv_glyph.c version.c
entab.o: entab.c cmassoc.h emalloc.c error.c files.h getoptv.c makepath.c match.c mergepath.c putoptv.c splitpath.c tabs.c tabs.h tabspec.c version.c vfopen.c
envp.o: envp.c
errno.o: errno.c
escv.o: escv.c chrindex.c chrlib.h chruesc.c strlib.h struesc.c todigit.c
ethcat.o: ethcat.c channel.c channel.h closechannel.c efreopen.c error.c error.h ether.h files.h flags.h getoptv.c getoptv.h hexdump.c hexencode.c memory.h number.h openchannel.c putoptv.c putoptv.h readpacket.c sendpacket.c todigit.c uintspec.c version.c
ether.o: ether.c
fbar.o: fbar.c clang.h cmassoc.h error.c fgetline.c files.h fputline.c getoptv.c linux.h makepath.c mergepath.c putoptv.c splitpath.c todigit.c uintspec.c version.c vfopen.c
ff-bld.o: ff-bld.c cmassoc.h error.c files.h find.c getoptv.c makefind.c makepath.c match.c mergepath.c partfile.c partpath.c putoptv.c showfind.c splitpath.c version.c
ff-elf.o: ff-elf.c chrcount.c chrlib.h cmassoc.h date.h datecomp.c emalloc.c error.c files.h find.c getoptv.c makefind.c makepath.c match.c mergepath.c partfile.c partpath.c putoptv.c splitpath.c strlib.h strsplit.c timecomp.c version.c
ff.o: ff.c chrcount.c chrlib.h cmassoc.h date.h datecomp.c emalloc.c error.c find.c getoptv.c makefind.c makepath.c match.c mergepath.c partfile.c partpath.c putoptv.c showfind.c splitpath.c strlib.h strsplit.c timecomp.c todigit.c uintspec.c version.c
filesize.o: filesize.c cmassoc.h console.c filepart.c todigit.c uintspec.c
footer.o: footer.c cmassoc.h console.c efreopen.c emalloc.c getviewport.c linux.h todigit.c uintspec.c
fp.o: fp.c SHA256.h SHA256Block.c SHA256Fetch.c SHA256Ident.c SHA256Reset.c SHA256Write.c cmassoc.h console.c crypt.h efreopen.c filepart.c hexout.c
getmem.o: getmem.c basespec.c error.c error.h files.h flags.h getoptv.c getoptv.h hexout.c memory.h number.h putoptv.c todigit.c types.h uintspec.c version.c
getmem2.o: getmem2.c basespec.c error.c error.h files.h flags.h getoptv.c getoptv.h hexout.c memdecode.c memory.h number.h putoptv.c todigit.c types.h uintspec.c version.c
getmode.o: getmode.c cmassoc.h files.h fputn.c ftype.c getoptv.c linux.h makefind.c makepath.c match.c mergepath.c partfile.c partpath.c putoptv.c splitpath.c version.c
go.o: go.c cgetc.c cmassoc.h command.c command.h emalloc.c error.c getoptv.c linux.h putoptv.c strlib.h tree.h version.c
grab.o: grab.c basespec.c efreopen.c error.c error.h files.h flags.h getoptv.c getoptv.h number.h putoptv.c putoptv.h todigit.c version.c version.h
graph.o: graph.c alert.c cmassoc.h efreopen.c error.c error_on_line.c getoptv.c putoptv.c todigit.c uintspec.c version.c
grope.o: grope.c charset.c chrlib.h chruesc.c chruescmap.c cmassoc.h console.c efreopen.c emalloc.c fgetline.c files.h find.c fputn.c makefind.c makepath.c match.c mergepath.c partfile.c partpath.c regex.h regexcomp.c regexfree.c regexhelp.c regexmake.c regexshow.c regexspan.c splitpath.c strlib.h struesc.c sv_ascii.c todigit.c uintspec.c vfopen.c
hbrief.o: hbrief.c chrlib.h clang.h cmassoc.h error.c files.h getoptv.c makepath.c mergepath.c nocontext.c noescaped.c noliteral.c putoptv.c splitpath.c tidy.h version.c vfopen.c
header.o: header.c cmassoc.h console.c efreopen.c emalloc.c getviewport.c linux.h todigit.c uintspec.c vtdef.h
hex.o: hex.c cmassoc.h efreopen.c error.c getoptv.c makepath.c match.c mergepath.c putoptv.c splitpath.c todigit.c version.c
hex2bin.o: hex2bin.c cmassoc.h error.c getoptv.c putoptv.c version.c
hexcmp.o: hexcmp.c cmassoc.h console.c
hexdmp.o: hexdmp.c cmassoc.h efreopen.c error.c getoptv.c putoptv.c todigit.c uintspec.c version.c
html.o: html.c efreopen.c error.c error.h format.h getoptv.c getoptv.h indent.c markup.h profile.c profile.h putoptv.c putoptv.h sizes.h totruth.c types.h version.c version.h
ifd.o: ifd.c cmassoc.h error.c getoptv.c putoptv.c todigit.c uintspec.c version.c
import.o: import.c cmassoc.h date.h error.c files.h find.c getoptv.c makefind.c makepath.c match.c mergepath.c partfile.c partpath.c putoptv.c splitpath.c todigit.c uintspec.c version.c
iplist.o: iplist.c IPAddr.c IPAddr.h IsIPv4.c cmassoc.h efreopen.c emalloc.c error.c getIPv4.c getoptv.c putoptv.c version.c
ipsort.o: ipsort.c IPAddr.h IsIPv4.c cmassoc.h efreopen.c emalloc.c error.c fgetline.c getIPv4.c getoptv.c putoptv.c strlib.h strsplit.c todigit.c uintspec.c version.c
key.o: key.c SHA256.h SHA256Block.c SHA256Fetch.c SHA256Print.c SHA256Reset.c SHA256Write.c cmassoc.h error.c getoptv.c putoptv.c strincr.c todigit.c uintspec.c version.c
l2p.o: l2p.c chars.h error.c error.h flags.h getoptv.c getoptv.h putoptv.c putoptv.h sizes.h version.c version.h
lam.o: lam.c cmassoc.h console.c emalloc.c link.h
localhost.o: localhost.c cmassoc.h console.c
log.o: log.c cmassoc.h console.c
long.o: long.c cmassoc.h error.c files.h getoptv.c makepath.c mergepath.c putoptv.c splitpath.c version.c vfopen.c
loop.o: loop.c error.c error.h getoptv.c getoptv.h number.h putoptv.c putoptv.h sizes.h todigit.c uintspec.c version.c version.h
lp2824.o: lp2824.c cmassoc.h console.c efopen.c
main.o: main.c cmassoc.h getoptv.c putoptv.c version.c
matrix.o: matrix.c chars.h date.h efreopen.c error.c error.h format.h getoptv.c getoptv.h getusername.c hostname.c indent.c linux.h markup.h number.h putoptv.c putoptv.h sizes.h todigit.c types.h uintspec.c username.c version.c version.h
matrix.old.o: matrix.old.c chars.h date.h efreopen.c error.c error.h format.h getoptv.c getoptv.h getusername.c hostname.c indent.c linux.h markup.h number.h putoptv.c putoptv.h sizes.h todigit.c types.h uintspec.c username.c version.c version.h
mmf.o: mmf.c arctime.c ccollect.c cinclude.c clang.h cmassoc.h efopen.c emalloc.c erealloc.c error.c error_on_line.c fgetline.c filename.c files.h getoptv.c havebreak.c havetoken.c isbreak.c isclass.c istoken.c list.h listappend.c listcreate.c listdelete.c listdetect.c listexpand.c listinsert.c listload.c listsort.c makepath.c mergepath.c nextbreak.c nexttoken.c partfile.c partpath.c putoptv.c scanalnum.c scanbreak.c scandigit.c scanflush.c scaninput.c scanspace.c scanstart.c scantoken.c scanuntil.c setfiletype.c splitpath.c strlib.h strwcmp.c tokentext.c version.c
mmf3.o: mmf3.c ccollect.c cinclude.c clang.h cmassoc.h efopen.c emalloc.c erealloc.c error.c error_on_line.c fgetline.c files.h getoptv.c havebreak.c havetoken.c isbreak.c isclass.c istoken.c list.h listappend.c listcreate.c listdelete.c listdetect.c listexpand.c listinsert.c listload.c makepath.c mergepath.c nextbreak.c nexttoken.c partfile.c partpath.c putoptv.c scanalnum.c scanbreak.c scandigit.c scanflush.c scaninput.c scanspace.c scanstart.c scantoken.c scanuntil.c setfiletype.c splitpath.c strlib.h strwcmp.c tokentext.c version.c
mmff.o: mmff.c cmassoc.h efopen.c emalloc.c erealloc.c error.c fgetline.c files.h getoptv.c havebreak.c havetoken.c isbreak.c istoken.c list.h listappend.c listcreate.c listdelete.c listdetect.c listexpand.c listinsert.c listload.c listsort.c makepath.c mergepath.c nextbreak.c nexttoken.c partfile.c partpath.c putoptv.c scan.h scanalnum.c scanbreak.c scandigit.c scanflush.c scaninput.c scanspace.c scanstart.c scantoken.c scanuntil.c splitpath.c strlib.h tokentext.c version.c
mp.o: mp.c cmassoc.h console.c makepath.c mergepath.c profile.c profile.h splitpath.c totruth.c vfopen.c
mrg.o: mrg.c adheap.c cmassoc.h console.c efopen.c emalloc.c enheap.c reheap.c sort.h swap.c todigit.c uintspec.c
munge.o: munge.c cmassoc.h console.c files.h makepath.c match.c mergepath.c splitpath.c vfopen.c
mvpkg.o: mvpkg.c cmassoc.h error.c error_on_line.c files.h getoptv.c makepath.c mergepath.c putoptv.c splitpath.c strlib.h strpkgcmp.c version.c
nics.o: nics.c decdecode.c decstring.c error.c error.h ether.h getoptv.c getoptv.h hexdecode.c hexstring.c hostnics.c memory.h putoptv.c putoptv.h types.h version.c version.h
np.o: np.c cmassoc.h error.c getoptv.c makepath.c mergepath.c putoptv.c splitpath.c version.c vfopen.c
octal.o: octal.c chrindex.c chrlib.h cmassoc.h efreopen.c error.c getoptv.c makepath.c mergepath.c putoptv.c splitpath.c version.c
ocomp.o: ocomp.c chars.h error.c error.h files.h flags.h getoptv.c getoptv.h hexoffset.c hexview.c memory.h number.h putoptv.c sizes.h version.c
odc.o: odc.c chars.h error.c error.h files.h flags.h getoptv.c getoptv.h hexoffset.c hexview.c memory.h number.h putoptv.c sizes.h version.c
odd.o: odd.c chars.h error.c error.h files.h flags.h getoptv.c getoptv.h hexoffset.c hexview.c memory.h number.h putoptv.c putoptv.h sizes.h version.c version.h
ode.o: ode.c basespec.c cmassoc.h console.c dataspec.c hexdump.c hexpeek.c memencode.c todigit.c uintspec.c
odump.o: odump.c chars.h error.c error.h files.h flags.h getoptv.c getoptv.h hexoffset.c hexview.c memory.h number.h putoptv.c putoptv.h sizes.h version.c version.h
odx.o: odx.c cmassoc.h console.c emalloc.c indent.c markup.h nodes.h xmlschema.c
oedit.o: oedit.c basespec.c cmassoc.h console.c dataspec.c hexdump.c hexpeek.c memencode.c todigit.c uintspec.c
offset.o: offset.c cmassoc.h console.c date.h efreopen.c emalloc.c format.h getusername.c hostname.c indent.c linux.h markup.h todigit.c uintspec.c username.c
order.o: order.c cmassoc.h edge.c edge.h efreopen.c emalloc.c erealloc.c error.c getoptv.c putoptv.c version.c
pad.o: pad.c cmassoc.h 
paginate.o: paginate.c cmassoc.h console.c efreopen.c filepart.c page.c page.h todigit.c uintspec.c
pkg.o: pkg.c chruesc.c cmassoc.h error.c fgetline.c getoptv.c putoptv.c strlib.h struesc.c todigit.c version.c
pkgdep.o: pkgdep.c charset.h cmassoc.h copytoken.c efreopen.c emalloc.c error.c fgetline.c files.h find.c getoptv.c havebreak.c havetoken.c isbreak.c isclass.c istoken.c match.c nextbreak.c nexttoken.c partfile.c partpath.c putoptv.c scan.h scanalnum.c scanbreak.c scandigit.c scanflush.c scaninput.c scanreset.c scanspace.c scantoken.c scanuntil.c scanwhile.c strlib.h strsplit.c tokensize.c tokentext.c version.c
pkgopt.o: pkgopt.c cmassoc.h efreopen.c error.c files.h getoptv.c putoptv.c version.c
preamble.o: preamble.c clang.h cmassoc.h error.c files.h getoptv.c linux.h makepath.c mergepath.c putoptv.c splitpath.c version.c vfopen.c
purge.o: purge.c cmassoc.h date.h error.c files.h find.c getoptv.c makefind.c makepath.c match.c mergepath.c partfile.c partpath.c putoptv.c splitpath.c todigit.c uintspec.c version.c
qc.o: qc.c cmassoc.h efopen.c emalloc.c erealloc.c error.c fgetline.c files.h fullpath.c getoptv.c havebreak.c havetoken.c isbreak.c istoken.c list.h listappend.c listcreate.c listdelete.c listexpand.c makepath.c mergepath.c nextbreak.c nexttoken.c partfile.c partpath.c putoptv.c scan.h scanalnum.c scanbreak.c scandigit.c scanflush.c scaninput.c scanreset.c scanspace.c scantoken.c scanuntil.c splitpath.c tokentext.c version.c
quiet.o: quiet.c cmassoc.h error.c getoptv.c putoptv.c version.c
radix.o: radix.c cmassoc.h error.c getoptv.c putoptv.c todigit.c uintspec.c version.c
relate.o: relate.c cmassoc.h depend.c depend.h efreopen.c emalloc.c error.c getoptv.c putoptv.c version.c
remove.o: remove.c charset.c chrlib.h chruesc.c chruescmap.c cmassoc.h console.c emalloc.c fgetline.c files.h fputline.c makepath.c mergepath.c regex.h regexcomp.c regexfree.c regexhelp.c regexmake.c regexshow.c regexspan.c splitpath.c strlib.h struesc.c sv_ascii.c todigit.c vfopen.c
rex.o: rex.c cmassoc.h console.c
rexp.o: rexp.c charset.c chrlib.h chruesc.c cmassoc.h emalloc.c error.c getoptv.c putoptv.c regex.h regexcomp.c regexfree.c regexmake.c regexshow.c regexspan.c todigit.c version.c
rmpkg.o: rmpkg.c cmassoc.h emalloc.c erealloc.c error.c find.c getoptv.c list.h listcreate.c listdelete.c listdetect.c listexpand.c listinsert.c makefind.c makepath.c match.c mergepath.c partfile.c partpath.c putoptv.c splitpath.c strlib.h strvercmp.c version.c
runjobs.o: runjobs.c cmassoc.h error.c files.h getoptv.c linux.h makefind.c makepath.c match.c mergepath.c partfile.c partpath.c plain.c putoptv.c setumask.c splitpath.c syslog.h syslog_basic.c syslog_error.c version.c
sbar.o: sbar.c chrlib.h clang.h cmassoc.h console.c linux.h makepath.c mergepath.c splitpath.c todigit.c uintspec.c vfopen.c
sbrief.o: sbrief.c cmassoc.h error.c files.h getoptv.c makepath.c mergepath.c putoptv.c splitpath.c version.c vfopen.c
search.o: search.c charset.c chrlib.h chruesc.c chruescmap.c cmassoc.h console.c efreopen.c emalloc.c fgetline.c files.h find.c fputn.c makefind.c makepath.c match.c mergepath.c partfile.c partpath.c regex.h regexcomp.c regexfree.c regexhelp.c regexmake.c regexshow.c regexspan.c showfind.c splitpath.c strlib.h struesc.c sv_ascii.c todigit.c uintspec.c
setmode.o: setmode.c atoin.c cmassoc.h efopen.c error.c getoptv.c linux.h putoptv.c version.c
setnumber.o: setnumber.c
shakey.o: shakey.c SHA256.h SHA256Block.c SHA256Fetch.c SHA256Print.c SHA256Reset.c SHA256Write.c cmassoc.h error.c getoptv.c putoptv.c version.c
shakeys.o: shakeys.c SHA256.h SHA256Block.c SHA256Fetch.c SHA256Print.c SHA256Reset.c SHA256Write.c cmassoc.h error.c getoptv.c putoptv.c version.c
shout.o: shout.c broadcast.c broadcast.h cmassoc.h emalloc.c error.c getoptv.c linux.h putoptv.c syslog.h syslog_basic.c syslog_error.c version.c
sign.o: sign.c cmassoc.h console.c signf.c todigit.c uintspec.c
sizeof.o: sizeof.c
space.o: space.c chrlib.h chruesc.c cmassoc.h console.c escaped.c keep.c literal.c makepath.c mergepath.c splitpath.c strlib.h struesc.c tidy.h todigit.c vfopen.c
srt.o: srt.c adheap.c cmassoc.h console.c deheap.c emalloc.c enheap.c makepath.c mergepath.c reheap.c sort.h splitpath.c swap.c todigit.c uintspec.c vfopen.c
stamp.o: stamp.c
str2hex.o: str2hex.c
sv.o: sv.c chrlib.h chrlwr.c chrupr.c cmassoc.h console.c efreopen.c fgetline.c indent.c serial.c strcomp.c strconv.c strlib.h strselect.c todigit.c uintspec.c
sweep.o: sweep.c cmassoc.h error.c files.h getoptv.c makepath.c mergepath.c putoptv.c splitpath.c version.c
symlinks.o: symlinks.c cmassoc.h console.c files.h find.c makefind.c makepath.c match.c mergepath.c partfile.c partpath.c showfind.c splitpath.c
syslog.o: syslog.c cmassoc.h date.h error.c files.h getoptv.c putoptv.c syslog.h syslog_basic.c syslog_encode.c syslog_facility_codes.c syslog_lookup.c syslog_severity_codes.c version.c
t1.o: t1.c
timer.o: timer.c
tls.o: tls.c cmassoc.h error.c getoptv.c indent.c putoptv.c todigit.c uintspec.c version.c
tr.o: tr.c charset.c chrlib.h chrset.c chrsub.c chruesc.c cmassoc.h error.c getoptv.c makepath.c mergepath.c putoptv.c splitpath.c version.c vfopen.c
trim.o: trim.c cmassoc.h console.c makepath.c mergepath.c splitpath.c todigit.c uintspec.c vfopen.c
try.o: try.c breakout.c console.c error.h format.h getoptv.h putoptv.h sizes.h version.h
ts.o: ts.c
ttcp.o: ttcp.c
typelist.o: typelist.c cmassoc.h efreopen.c error.c getoptv.c indent.c print.c putoptv.c symbol.h todigit.c typeload.c typesave.c version.c
undash.o: undash.c cmassoc.h error.c files.h getoptv.c makepath.c mergepath.c putoptv.c splitpath.c version.c vfopen.c
unique.o: unique.c cmassoc.h console.c efreopen.c emalloc.c makepath.c match.c mergepath.c splitpath.c todigit.c uintspec.c
vl.o: vl.c ascii.h charset.h cmassoc.h error.c files.h getoptv.c makepath.c match.c mergepath.c putoptv.c splitpath.c todigit.c uintspec.c version.c vfopen.c
vr.o: vr.c ascii.h charset.h cmassoc.h error.c files.h getoptv.c makepath.c match.c mergepath.c putoptv.c splitpath.c todigit.c uintspec.c version.c vfopen.c
vu.o: vu.c chrlib.h cmassoc.h console.c efreopen.c sv_ascii.c sv_glyph.c
wc.o: wc.c charset.c chrdef.c chrlib.h chrset.c cmassoc.h efreopen.c error.c getoptv.c putoptv.c version.c
what.o: what.c cmassoc.h console.c emalloc.c erealloc.c getviewport.c linux.h list.h listcolumn.c listcreate.c listdelete.c listdetect.c listexpand.c listinsert.c procstat.h strlib.h strsplit.c todigit.c uintspec.c
whom.o: whom.c charset.c chrlib.h chruesc.c chruescmap.c cmassoc.h console.c emalloc.c erealloc.c getviewport.c linux.h list.h listcolumn.c listcreate.c listdelete.c listdetect.c listexpand.c listinsert.c regex.h regexcomp.c regexfree.c regexhelp.c regexmake.c regexshow.c regexspan.c sv_ascii.c todigit.c uintspec.c
wl.o: wl.c charset.c chrdef.c chrlib.h chrlwr.c chrset.c chrupr.c cmassoc.h efreopen.c error.c getoptv.c putoptv.c strcomp.c strconv.c version.c
xde.o: xde.c cmassoc.h console.c emalloc.c hexdump.c indent.c nodes.h reorder.c svindex.c todigit.c uintspec.c xmledit.c xmlfree.c xmlnode.c xmlopen.c xmlsample.c xmlscan.c xmlschema.c
xml.o: xml.c _xmlattribute.c _xmlvalue.c cmassoc.h console.c emalloc.c indent.c nodes.h reorder.c xmlfree.c xmlindent.c xmlnode.c xmlread.c xmlscan.c xmlstream.c xmltree.c



