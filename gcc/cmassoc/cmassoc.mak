# file: cmassoc/cmassoc.mak

# ====================================================================
# programs;
# --------------------------------------------------------------------

_basic.o: _basic.c cmassoc.h
_main.o: _main.c
afm.o: afm.c ascii.h chrlib.h cmassoc.h tabs.h
align.o: align.c chrlib.h cmassoc.h strlib.h
argv.o: argv.c
argvesc.o: argvesc.c chrlib.h strlib.h
auth.o: auth.c clang.h cmassoc.h linux.h
b64.o: b64.c base64.h cmassoc.h error.h
bang.o: bang.c clang.h cmassoc.h files.h linux.h
bin2hex.o: bin2hex.c cmassoc.h
blank.o: blank.c cmassoc.h files.h
calend.o: calend.c cmassoc.h date.h
call.o: call.c cmassoc.h strlib.h tidy.h
case.o: case.c chrlib.h cmassoc.h strlib.h tidy.h
cat.o: cat.c cmassoc.h
catalog.o: catalog.c cmassoc.h format.h markup.h
cblock.o: cblock.c chars.h cmassoc.h tidy.h
cbrief.o: cbrief.c cmassoc.h tidy.h
cdep.o: cdep.c cmassoc.h depend.h scan.h
cedit.o: cedit.c cmassoc.h
change.o: change.c chrlib.h cmassoc.h files.h regex.h strlib.h
checkmode.o: checkmode.c cmassoc.h linux.h
chkbld.o: chkbld.c cmassoc.h files.h scan.h
chperm.o: chperm.c cmassoc.h files.h
chr.o: chr.c chrlib.h cmassoc.h
cinc.o: cinc.c chrlib.h clang.h cmassoc.h
clear.o: clear.c cmassoc.h
cmerge.o: cmerge.c clang.h cmassoc.h date.h linux.h list.h scan.h
cpp2c.o: cpp2c.c chrlib.h clang.h cmassoc.h tidy.h
crlf.o: crlf.c cmassoc.h files.h
csv2html.o: csv2html.c cmassoc.h format.h markup.h
ctar.o: ctar.c clang.h cmassoc.h list.h scan.h
define.o: define.c cmassoc.h markup.h symbol.h
defix.o: defix.c cmassoc.h strlib.h
delta.o: delta.c cmassoc.h
detab.o: detab.c cmassoc.h files.h tabs.h
detag.o: detag.c cmassoc.h tidy.h
dif.o: dif.c cmassoc.h link.h
dls.o: dls.c cmassoc.h linux.h list.h
dmp2hex.o: dmp2hex.c cmassoc.h
ds.o: ds.c SHA256.h error.h files.h getoptv.h sizes.h
dump.o: dump.c chrlib.h cmassoc.h
efru.o: efru.c channel.h error.h flags.h getoptv.h memory.h number.h putoptv.h types.h
efsu.o: efsu.c channel.h error.h flags.h getoptv.h memory.h number.h putoptv.h symbol.h
enbrace.o: enbrace.c cmassoc.h
enfix.o: enfix.c chrlib.h cmassoc.h strlib.h
englyph.o: englyph.c chrlib.h cmassoc.h strlib.h
entab.o: entab.c cmassoc.h files.h tabs.h
envp.o: envp.c
errno.o: errno.c
escv.o: escv.c chrlib.h strlib.h
ethcat.o: ethcat.c channel.h error.h ether.h files.h flags.h getoptv.h memory.h number.h putoptv.h
ether.o: ether.c
fbar.o: fbar.c clang.h cmassoc.h files.h linux.h
ff-bld.o: ff-bld.c cmassoc.h files.h
ff-elf.o: ff-elf.c chrlib.h cmassoc.h date.h files.h strlib.h
ff.o: ff.c chrlib.h cmassoc.h date.h strlib.h
filesize.o: filesize.c cmassoc.h
footer.o: footer.c cmassoc.h linux.h
fp.o: fp.c SHA256.h cmassoc.h crypt.h
getmem.o: getmem.c error.h files.h flags.h getoptv.h memory.h number.h types.h
getmem2.o: getmem2.c error.h files.h flags.h getoptv.h memory.h number.h types.h
getmode.o: getmode.c cmassoc.h files.h linux.h
go.o: go.c cmassoc.h command.h linux.h strlib.h tree.h
grab.o: grab.c error.h files.h flags.h getoptv.h number.h putoptv.h version.h
graph.o: graph.c cmassoc.h
grope.o: grope.c chrlib.h cmassoc.h files.h regex.h strlib.h
hbrief.o: hbrief.c chrlib.h clang.h cmassoc.h files.h tidy.h
header.o: header.c cmassoc.h linux.h vtdef.h
hex.o: hex.c cmassoc.h
hex2bin.o: hex2bin.c cmassoc.h
hexcmp.o: hexcmp.c cmassoc.h
hexdmp.o: hexdmp.c cmassoc.h
html.o: html.c error.h format.h getoptv.h markup.h profile.h putoptv.h sizes.h types.h version.h
ifd.o: ifd.c cmassoc.h
import.o: import.c cmassoc.h date.h files.h
iplist.o: iplist.c IPAddr.h cmassoc.h
ipsort.o: ipsort.c IPAddr.h cmassoc.h strlib.h
key.o: key.c SHA256.h cmassoc.h
l2p.o: l2p.c chars.h error.h flags.h getoptv.h putoptv.h sizes.h version.h
lam.o: lam.c cmassoc.h link.h
localhost.o: localhost.c cmassoc.h
log.o: log.c cmassoc.h
long.o: long.c cmassoc.h files.h
loop.o: loop.c error.h getoptv.h number.h putoptv.h sizes.h version.h
lp2824.o: lp2824.c cmassoc.h
main.o: main.c cmassoc.h
matrix.o: matrix.c chars.h date.h error.h format.h getoptv.h linux.h markup.h number.h putoptv.h sizes.h types.h version.h
mmf.o: mmf.c clang.h cmassoc.h files.h list.h strlib.h
mp.o: mp.c chars.h console.h error.h files.h profile.h sizes.h tidy.h
mp2.o: mp2.c chars.h console.h error.h files.h profile.h sizes.h tidy.h
mrg.o: mrg.c cmassoc.h sort.h
munge.o: munge.c cmassoc.h files.h
mvpkg.o: mvpkg.c cmassoc.h files.h strlib.h
nics.o: nics.c error.h ether.h getoptv.h memory.h putoptv.h types.h version.h
np.o: np.c cmassoc.h
ocomp.o: ocomp.c chars.h error.h files.h flags.h getoptv.h memory.h number.h sizes.h
octal.o: octal.c chrlib.h cmassoc.h
odc.o: odc.c chars.h error.h files.h flags.h getoptv.h memory.h number.h sizes.h
odd.o: odd.c chars.h error.h files.h flags.h getoptv.h memory.h number.h putoptv.h sizes.h version.h
ode.o: ode.c cmassoc.h
odump.o: odump.c chars.h error.h files.h flags.h getoptv.h memory.h number.h putoptv.h sizes.h version.h
odx.o: odx.c cmassoc.h markup.h nodes.h
oedit.o: oedit.c cmassoc.h
offset.o: offset.c cmassoc.h date.h format.h linux.h markup.h
order.o: order.c cmassoc.h edge.h
owrt.o: owrt.c flags.h getoptv.h
pad.o: pad.c cmassoc.h
paginate.o: paginate.c cmassoc.h page.h
pkg.o: pkg.c cmassoc.h strlib.h
pkgdep.o: pkgdep.c charset.h cmassoc.h files.h scan.h strlib.h
pkgopt.o: pkgopt.c cmassoc.h files.h
preamble.o: preamble.c clang.h cmassoc.h files.h linux.h
purge.o: purge.c cmassoc.h date.h files.h
qc.o: qc.c cmassoc.h files.h list.h scan.h
quiet.o: quiet.c cmassoc.h
radix.o: radix.c cmassoc.h
relate.o: relate.c cmassoc.h depend.h
remove.o: remove.c chrlib.h cmassoc.h files.h regex.h strlib.h
rex.o: rex.c cmassoc.h
rexp.o: rexp.c chrlib.h cmassoc.h regex.h
rmpkg.o: rmpkg.c cmassoc.h list.h strlib.h
runjobs.o: runjobs.c cmassoc.h files.h linux.h syslog.h
sbar.o: sbar.c chrlib.h clang.h cmassoc.h linux.h
sbrief.o: sbrief.c cmassoc.h files.h
search.o: search.c chrlib.h cmassoc.h files.h regex.h strlib.h
setmode.o: setmode.c cmassoc.h linux.h
setnumber.o: setnumber.c
shakey.o: shakey.c SHA256.h cmassoc.h
shakeys.o: shakeys.c SHA256.h cmassoc.h
shout.o: shout.c broadcast.h cmassoc.h linux.h syslog.h
sign.o: sign.c cmassoc.h
single.o: single.c cmassoc.h
sizeof.o: sizeof.c
space.o: space.c chrlib.h cmassoc.h strlib.h tidy.h
srt.o: srt.c cmassoc.h sort.h
stamp.o: stamp.c
str2hex.o: str2hex.c
sv.o: sv.c chrlib.h cmassoc.h strlib.h
sweep.o: sweep.c cmassoc.h files.h
symlinks.o: symlinks.c cmassoc.h files.h
syslog.o: syslog.c cmassoc.h date.h files.h syslog.h
timer.o: timer.c
tls.o: tls.c cmassoc.h
tr.o: tr.c chrlib.h cmassoc.h
trim.o: trim.c cmassoc.h
try.o: try.c error.h format.h getoptv.h putoptv.h sizes.h version.h
ts.o: ts.c
ttcp.o: ttcp.c
typelist.o: typelist.c cmassoc.h symbol.h
undash.o: undash.c cmassoc.h files.h
unique.o: unique.c cmassoc.h
vl.o: vl.c ascii.h charset.h cmassoc.h files.h
vr.o: vr.c ascii.h charset.h cmassoc.h files.h
vu.o: vu.c chrlib.h cmassoc.h
wc.o: wc.c chrlib.h cmassoc.h
what.o: what.c cmassoc.h linux.h list.h procstat.h strlib.h
whom.o: whom.c chrlib.h cmassoc.h linux.h list.h regex.h
wl.o: wl.c chrlib.h cmassoc.h
xde.o: xde.c cmassoc.h nodes.h
xml.o: xml.c cmassoc.h nodes.h



