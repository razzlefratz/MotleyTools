#!bin/make -f
# file: cmassoc/Makefile
# Published 2005 by Charles Maier Associates Limited for internal use;

# ====================================================================
# environment;
# --------------------------------------------------------------------

include ../make.def

# ====================================================================
# symbols;
# --------------------------------------------------------------------

CFLAGS=-Wall -Wextra -Wno-unused-parameter -DMAKEFILE -D_GNU_SOURCE -D__GETOPT_H__ -D_GETOPT_DEFINED_
LFLAGS=
VPATH=../chrlib:../date:../files:../linux:../ether:../link:../list:../regex:../scan:../sort:../strlib:../sv:../tools:../tree:../nodes:../clang:../sysklogd:../tidy:../crypt
TRASH=*.o *.obj *.exe t t.c *~ *.[0-9][0-9][0-9] *.stackdump

MAKEFIND=makefind.o partpath.o partfile.o find.o
MAKEPATH=makepath.o splitpath.o mergepath.o
VFOPEN=vfopen.o ${MAKEPATH}

TOOLS=afm align argv argvesc b64 bang bin2hex blank calend call envp ether case catalog cblock cbrief cdep cedit change chr cinc cmerge cpp2c crlf csv2html ctar defix delta detab detag dls dmp2hex dump ds efru efsu enbrace enfix englyph entab errno fbar ff filesize footer fp go grab graph grope hbrief header hex hex2bin hexcmp hexdmp html ifd import iplist ipsort key l2p lp2824 lam log loop matrix mmf mp mrg munge rex nics np ocomp odc odd ode odump odx oedit offset ofld order owrt pad paginate preamble purge radix relate remove sbar sbrief search shakey shakeys sign single sizeof space srt stamp sv sweep symlinks timer typelist tls trim try ts unique vl vu wl xde xml 

PAGES=toolkit.1 afm.1 align.1 argv.1 b64.1 bang.1 bin2hex.1 blank.1 calend.1 call.1 case.1 catalog.1 cblock.1 cbrief.1 cdep.1 cedit.1 change.1 chr.1 cinc.1 cmerge.1 crlf.1 csv2html.1 ctar.1 defix.1 delta.1 detab.1 detag.1 dls.1 dmp2hex.1 ds.1 efsu.1 enbrace.1 enfix.1 englyph.1 entab.1 envp.1 fbar.1 ff.1 filesize.1 footer.1 fp.1 grab.1 graph.1 grope.1 hbrief.1 header.1 hex.1 hex2bin.1 hexcmp.1 hexdmp.1 html.1 ifd.1 import.1 key.1 l2p.1 lam.1 log.1 loop.1 matrix.1 mp.1 mrg.1 munge.1 nics.1 np.1 ocomp.1 odc.1 odd.1 ode.1 odump.1 odx.1 oedit.1 offset.1 order.1 preamble.1 relate.1 remove.1 rex.1 sbrief.1 search.1 shakey.1 shakeys.1 single.1 sizeof.1 space.1 srt.1 stamp.1 sweep.1 sv.1 symlinks.1 timer.1 typelist.1 tls.1 trim.1 try.1 unique.1 vl.1 vu.1 wl.1 xde.1 xml.1

ifeq (${OS},linux)
TOOLS+=localhost quiet runjobs shout syslog what whom
PAGES+=localhost.1 quiet.1 runjobs.1 shout.1 what.1 whom.1
endif

# TOOLS+=long mvpkg octal pkgdep pkgopt qc rexp rmpkg chkbld chperm checkmode dif ff-bld ff-elf setmode undash 
# PAGES+=long.1 mvpkg.1 octal.1 pkgdep.1 pkgopt.1 qc.1 rexp.1 rmpkg.1 chkbld.1 chperm.1 checkmode.1 dif.1 ff-bld.1 ff-elf.1 setmode.1 undash.1 

# TOOLS+=mycat mytr mywc 
# PAGES+=tr.1 

OTHER=auth cat checkmode chkbld chperm clear define dif dump ff-bld ff-elf localhostlong main mvpkg octal pkg pkgdep pkgopt qc quiet rexp rmpkg runjobs setmode shout tr undash wc what whom

# ====================================================================
# targets;
# --------------------------------------------------------------------

compile: ${TOOLS}
scripts:
manuals:
	install -m 0444 -o ${OWNER} -g ${GROUP} ${PAGES} ${MAN}
install: compile library
	install -m 0555 -o ${OWNER} -g ${GROUP} ${TOOLS} ${BIN}
	if [ -d /etc/profile.d ]; then install -m 0775 -o root -g root ../../misc/motley-tools.sh /etc/profile.d; fi;
library:
	install -m 6775 -o ${OWNER} -g ${GROUP} -d ${BIN}
uninstall:
	if [ -d /etc/profile ]; then rm -fr /etc/profile.d/motley-tools.sh; fi;
	cd ${BIN}; rm -fv ${TOOLS}
	cd ${MAN}; rm -fv ${PAGES}
fresh: clean compile
clean:
	rm -f ${TRASH} ${TOOLS}
	chmod 0755 Makefile *.sh
	chmod 0644 *.c 
check:
	${SH} cmassoc.sh
ignore:
	echo ${TOOLS} ${OTHER} | tr " " "\n" > .gitignore

# ====================================================================
# targets;
# --------------------------------------------------------------------

afm: afm.o chrupr.o emalloc.o error.o getoptv.o makepath.o mergepath.o putoptv.o splitpath.o strcomp.o strconv.o tabs.o tabspec.o todigit.o uintspec.o version.o vfopen.o
align: align.o chrindex.o chruesc.o error.o getoptv.o makepath.o mergepath.o putoptv.o splitpath.o struesc.o todigit.o uintspec.o version.o vfopen.o
argv: argv.o
argvesc: argvesc.o chrindex.o chruesc.o struesc.o todigit.o
auth: auth.o efreopen.o error.o getoptv.o putoptv.o version.o
b64: b64.o error.o getoptv.o makepath.o mergepath.o putoptv.o splitpath.o todigit.o uintspec.o version.o vfopen.o
bang: bang.o error.o find.o getoptv.o makefind.o makepath.o mergepath.o partfile.o partpath.o putoptv.o splitpath.o version.o vfopen.o
bin2hex: bin2hex.o efreopen.o error.o getoptv.o putoptv.o todigit.o uintspec.o version.o
blank: blank.o console.o makepath.o mergepath.o splitpath.o todigit.o uintspec.o vfopen.o
calend: calend.o dayofwk.o endofmo.o error.o getoptv.o isleap.o putoptv.o sintspec.o sv_date1.o sv_month.o version.o
call: call.o console.o efreopen.o nocomment.o nocontext.o noescaped.o noliteral.o svindex.o
case: case.o chrlwr.o chrupr.o error.o escaped.o getoptv.o keep.o literal.o makepath.o mergepath.o putoptv.o splitpath.o strcomp.o strconv.o version.o vfopen.o
cat: cat.o efreopen.o error.o getoptv.o putoptv.o todigit.o uintspec.o version.o
catalog: catalog.o emalloc.o error.o filepart.o getoptv.o indent.o makepath.o mergepath.o putoptv.o splitpath.o todigit.o uintspec.o version.o vfopen.o
cblock: cblock.o capsule.o comment.o content.o context.o control.o error.o escaped.o fortran.o getoptv.o keep.o literal.o makepath.o mergepath.o putoptv.o splitpath.o version.o vfopen.o
cbrief: cbrief.o console.o escaped.o keep.o literal.o makepath.o mergepath.o nocomment.o splitpath.o vfopen.o
cdep: cdep.o depend.o efopen.o emalloc.o erealloc.o error.o fgetline.o find.o fullpath.o getoptv.o havebreak.o havetoken.o isbreak.o istoken.o makepath.o mergepath.o nextbreak.o nexttoken.o partfile.o partpath.o putoptv.o scanalnum.o scanbreak.o scandigit.o scanflush.o scaninput.o scanspace.o scanstart.o scantoken.o scanuntil.o splitpath.o tokentext.o version.o
cedit: cedit.o error.o getoptv.o makepath.o mergepath.o putoptv.o splitpath.o version.o vfopen.o
change: change.o charset.o chrindex.o chruesc.o chruescmap.o emalloc.o error.o fgetline.o getoptv.o makefind.o makepath.o match.o mergepath.o partfile.o partpath.o putoptv.o regexcomp.o regexfree.o regexhelp.o regexmake.o regexshow.o regexspan.o splitpath.o struesc.o sv_ascii.o todigit.o version.o vfopen.o
checkmode: checkmode.o atoin.o efopen.o error.o getoptv.o putoptv.o version.o
chkbld: chkbld.o efreopen.o emalloc.o error.o fgetline.o getoptv.o havebreak.o havetoken.o isbreak.o istoken.o nextbreak.o nexttoken.o putoptv.o scanalnum.o scandigit.o scanflush.o scaninput.o scanreset.o scanspace.o scantoken.o scanuntil.o tokentext.o version.o
chperm: chperm.o error.o find.o getoptv.o makefind.o makepath.o match.o mergepath.o modespec.o partfile.o partpath.o putoptv.o splitpath.o version.o
chr: chr.o efreopen.o error.o getoptv.o putoptv.o sv_ascii.o version.o
cinc: cinc.o efopen.o error.o getoptv.o makepath.o mergepath.o putoptv.o splitpath.o version.o
clear: clear.o console.o
cmerge: cmerge.o efopen.o emalloc.o erealloc.o error.o getoptv.o getusername.o havebreak.o havetoken.o isbreak.o istoken.o listappend.o listcreate.o listdelete.o listexpand.o listrubout.o makefind.o makepath.o mergepath.o nextbreak.o nexttoken.o partfile.o partpath.o putoptv.o scanalnum.o scandigit.o scanflush.o scaninput.o scanspace.o scanstart.o scantoken.o scanuntil.o splitpath.o tokentext.o version.o
cpp2c: cpp2c.o error.o escaped.o fortran.o getoptv.o keep.o literal.o makepath.o mergepath.o putoptv.o splitpath.o version.o vfopen.o
crlf: crlf.o console.o makepath.o mergepath.o splitpath.o vfopen.o
csv2html: csv2html.o console.o efreopen.o filepart.o indent.o todigit.o uintspec.o
ctar: ctar.o ccollect.o cinclude.o emalloc.o erealloc.o error.o error_on_line.o fgetline.o havebreak.o havetoken.o isbreak.o istoken.o listappend.o listcreate.o listexpand.o makepath.o mergepath.o nextbreak.o nexttoken.o partfile.o partpath.o scanalnum.o scanbreak.o scandigit.o scanflush.o scaninput.o scanreset.o scanspace.o scanstart.o scantoken.o scanuntil.o splitpath.o tokentext.o
define: define.o console.o efreopen.o indent.o todigit.o typeload.o typesave.o
defix: defix.o chruesc.o console.o struesc.o todigit.o
delta: delta.o efreopen.o error.o error_on_line.o getoptv.o putoptv.o todigit.o uintspec.o version.o
detab: detab.o emalloc.o error.o getoptv.o makepath.o match.o mergepath.o putoptv.o splitpath.o tabs.o tabspec.o version.o vfopen.o
detag: detag.o console.o efreopen.o keep.o nocomment.o nocontent.o nocontext.o noescaped.o noliteral.o todigit.o uintspec.o
dif: dif.o efopen.o efreopen.o emalloc.o error.o getoptv.o makeitem.o putoptv.o queue.o todigit.o uintspec.o version.o
dls: dls.o console.o emalloc.o erealloc.o getviewport.o listcolumn.o listcreate.o listdelete.o listdetect.o listexpand.o listinsert.o todigit.o uintspec.o
dmp2hex: dmp2hex.o error.o getoptv.o putoptv.o version.o
ds: ds.o SHA256Block.o SHA256Fetch.o SHA256Ident.o SHA256Match.o SHA256Reset.o SHA256Write.o console.o efreopen.o
dump: dump.o console.o
efru: efru.o basespec.o channel.o closechannel.o error.o getoptv.o hexdecode.o hexdump.o hexstring.o openchannel.o putoptv.o readpacket.o sendpacket.o todigit.o uintspec.o version.o
efsu: efsu.o basespec.o channel.o closechannel.o error.o getoptv.o hexdump.o hexencode.o hexload.o openchannel.o putoptv.o readpacket.o sendpacket.o todigit.o uintspec.o version.o
enbrace: enbrace.o error.o getoptv.o makepath.o mergepath.o putoptv.o splitpath.o version.o vfopen.o
enfix: enfix.o chruesc.o error.o getoptv.o makepath.o mergepath.o putoptv.o splitpath.o struesc.o todigit.o version.o vfopen.o
englyph: englyph.o efreopen.o emalloc.o error.o getoptv.o putoptv.o strfglyph.o sv_glyph.o version.o
entab: entab.o emalloc.o error.o getoptv.o makepath.o match.o mergepath.o putoptv.o splitpath.o tabs.o tabspec.o version.o vfopen.o
envp: envp.o
errno: errno.o
escv: escv.o chrindex.o chruesc.o struesc.o todigit.o
ethcat: ethcat.o channel.o closechannel.o efreopen.o error.o getoptv.o hexdump.o hexencode.o openchannel.o putoptv.o readpacket.o sendpacket.o todigit.o uintspec.o version.o
ether: ether.o
fbar: fbar.o error.o fgetline.o fputline.o getoptv.o makepath.o mergepath.o putoptv.o splitpath.o todigit.o uintspec.o version.o vfopen.o
ff-bld: ff-bld.o error.o find.o getoptv.o makefind.o makepath.o match.o mergepath.o partfile.o partpath.o putoptv.o showfind.o splitpath.o version.o
ff-elf: ff-elf.o chrcount.o datecomp.o emalloc.o error.o find.o getoptv.o makefind.o makepath.o match.o mergepath.o partfile.o partpath.o putoptv.o splitpath.o strsplit.o timecomp.o version.o
ff: ff.o chrcount.o datecomp.o emalloc.o error.o find.o getoptv.o makefind.o makepath.o match.o mergepath.o partfile.o partpath.o putoptv.o showfind.o splitpath.o strsplit.o timecomp.o todigit.o uintspec.o version.o
filesize: filesize.o console.o filepart.o todigit.o uintspec.o
footer: footer.o console.o efreopen.o emalloc.o getviewport.o todigit.o uintspec.o
fp: fp.o SHA256Block.o SHA256Fetch.o SHA256Ident.o SHA256Reset.o SHA256Write.o console.o efreopen.o filepart.o hexout.o
getmem: getmem.o basespec.o error.o getoptv.o hexout.o putoptv.o todigit.o uintspec.o version.o
getmem2: getmem2.o basespec.o error.o getoptv.o hexout.o memdecode.o putoptv.o todigit.o uintspec.o version.o
getmode: getmode.o fputn.o ftype.o getoptv.o makefind.o makepath.o match.o mergepath.o partfile.o partpath.o putoptv.o splitpath.o version.o
go: go.o cgetc.o command.o emalloc.o error.o getoptv.o putoptv.o version.o
grab: grab.o basespec.o efreopen.o error.o getoptv.o putoptv.o todigit.o version.o
graph: graph.o alert.o efreopen.o error.o error_on_line.o getoptv.o putoptv.o sintspec.o todigit.o uintspec.o version.o
grope: grope.o charset.o chruesc.o chruescmap.o console.o efreopen.o emalloc.o fgetline.o find.o fputn.o makefind.o makepath.o match.o mergepath.o partfile.o partpath.o regexcomp.o regexfree.o regexhelp.o regexmake.o regexshow.o regexspan.o splitpath.o struesc.o sv_ascii.o todigit.o uintspec.o vfopen.o
hbrief: hbrief.o error.o getoptv.o keep.o makepath.o mergepath.o nocontext.o noescaped.o noliteral.o putoptv.o splitpath.o version.o vfopen.o
header: header.o console.o efreopen.o emalloc.o getviewport.o todigit.o uintspec.o
hex: hex.o efreopen.o error.o getoptv.o makepath.o match.o mergepath.o putoptv.o splitpath.o todigit.o version.o
hex2bin: hex2bin.o error.o getoptv.o putoptv.o version.o
hexcmp: hexcmp.o console.o
hexdmp: hexdmp.o efreopen.o error.o getoptv.o putoptv.o todigit.o uintspec.o version.o
html: html.o efreopen.o error.o getoptv.o indent.o profile.o putoptv.o totruth.o version.o
ifd: ifd.o error.o getoptv.o putoptv.o todigit.o uintspec.o version.o
import: import.o error.o find.o getoptv.o makefind.o makepath.o match.o mergepath.o partfile.o partpath.o putoptv.o splitpath.o todigit.o uintspec.o version.o
iplist: iplist.o IPAddr.o IsIPv4.o efreopen.o emalloc.o error.o getIPv4.o getoptv.o putoptv.o version.o
ipsort: ipsort.o IsIPv4.o efreopen.o emalloc.o error.o fgetline.o getIPv4.o getoptv.o putoptv.o strsplit.o todigit.o uintspec.o version.o
key: key.o SHA256Block.o SHA256Fetch.o SHA256Print.o SHA256Reset.o SHA256Write.o error.o getoptv.o putoptv.o strincr.o todigit.o uintspec.o version.o
l2p: l2p.o error.o getoptv.o putoptv.o version.o
lam: lam.o console.o emalloc.o
localhost: localhost.o console.o
log: log.o console.o
long: long.o error.o getoptv.o makepath.o mergepath.o putoptv.o splitpath.o version.o vfopen.o
loop: loop.o error.o getoptv.o putoptv.o todigit.o uintspec.o version.o
lp2824: lp2824.o console.o efopen.o
main: main.o getoptv.o putoptv.o version.o
matrix: matrix.o efreopen.o error.o getoptv.o getusername.o hostname.o indent.o putoptv.o todigit.o uintspec.o username.o version.o
mmf: mmf.o arctime.o ccollect.o cinclude.o efopen.o emalloc.o erealloc.o error.o error_on_line.o fgetline.o filename.o getoptv.o havebreak.o havetoken.o isbreak.o isclass.o istoken.o listappend.o listcreate.o listdelete.o listdetect.o listexpand.o listinsert.o listload.o listsort.o makepath.o mergepath.o nextbreak.o nexttoken.o partfile.o partpath.o putoptv.o scanalnum.o scanbreak.o scandigit.o scanflush.o scaninput.o scanspace.o scanstart.o scantoken.o scanuntil.o setfiletype.o splitpath.o strwcmp.o tokentext.o version.o
mp: mp.o console.o makepath.o mergepath.o profile.o splitpath.o totruth.o vfopen.o literal.o escaped.o keep.o
mrg: mrg.o adheap.o console.o efopen.o emalloc.o enheap.o reheap.o swap.o todigit.o uintspec.o
munge: munge.o console.o makepath.o match.o mergepath.o splitpath.o vfopen.o
mvpkg: mvpkg.o error.o error_on_line.o getoptv.o makepath.o mergepath.o putoptv.o splitpath.o strpkgcmp.o version.o
nics: nics.o decdecode.o decstring.o error.o getoptv.o hexdecode.o hexstring.o hostnics.o putoptv.o version.o
np: np.o error.o getoptv.o makepath.o mergepath.o putoptv.o splitpath.o version.o vfopen.o
octal: octal.o chrindex.o efreopen.o error.o getoptv.o makepath.o mergepath.o putoptv.o splitpath.o version.o
ocomp: ocomp.o error.o getoptv.o hexoffset.o hexview.o putoptv.o version.o
odc: odc.o error.o getoptv.o hexoffset.o hexview.o putoptv.o version.o
odd: odd.o error.o getoptv.o hexoffset.o hexview.o putoptv.o version.o
ode: ode.o basespec.o console.o dataspec.o hexdump.o hexpeek.o memencode.o todigit.o uintspec.o
ode2: ode2.o basespec.o dataspec.o error.o getoptv.o hexdump.o putoptv.o todigit.o uintspec.o version.o
odump: odump.o error.o getoptv.o hexoffset.o hexview.o putoptv.o version.o
odx: odx.o console.o indent.o xmlschema.o
oedit: oedit.o basespec.o console.o dataspec.o hexdump.o hexpeek.o memencode.o todigit.o uintspec.o
offset: offset.o console.o efreopen.o emalloc.o getusername.o hostname.o indent.o todigit.o uintspec.o username.o
ofld: ofld.o efreopen.o error.o getfields.o getoptv.o putoptv.o version.o uintspec.o todigit.o
order: order.o edge.o efreopen.o emalloc.o erealloc.o error.o getoptv.o putoptv.o version.o
owrt: owrt.o efreopen.o error.o getfields.o getoptv.o putoptv.o version.o
pad: pad.o efreopen.o error.o getoptv.o putoptv.o todigit.o uintspec.o version.o
paginate: paginate.o console.o efreopen.o filepart.o page.o todigit.o uintspec.o
pkg: pkg.o chruesc.o error.o fgetline.o getoptv.o putoptv.o struesc.o todigit.o version.o
pkgdep: pkgdep.o copytoken.o efreopen.o emalloc.o error.o fgetline.o find.o getoptv.o havebreak.o havetoken.o isbreak.o isclass.o istoken.o match.o nextbreak.o nexttoken.o partfile.o partpath.o putoptv.o scanalnum.o scanbreak.o scandigit.o scanflush.o scaninput.o scanreset.o scanspace.o scantoken.o scanuntil.o scanwhile.o strsplit.o tokensize.o tokentext.o version.o
pkgopt: pkgopt.o efreopen.o error.o getoptv.o putoptv.o version.o
preamble: preamble.o error.o getoptv.o makepath.o mergepath.o putoptv.o splitpath.o version.o vfopen.o
purge: purge.o error.o find.o getoptv.o makefind.o makepath.o match.o mergepath.o partfile.o partpath.o putoptv.o splitpath.o todigit.o uintspec.o version.o
qc: qc.o efopen.o emalloc.o erealloc.o error.o fgetline.o fullpath.o getoptv.o havebreak.o havetoken.o isbreak.o istoken.o listappend.o listcreate.o listdelete.o listexpand.o makepath.o mergepath.o nextbreak.o nexttoken.o partfile.o partpath.o putoptv.o scanalnum.o scanbreak.o scandigit.o scanflush.o scaninput.o scanreset.o scanspace.o scantoken.o scanuntil.o splitpath.o tokentext.o version.o
quiet: quiet.o error.o getoptv.o putoptv.o version.o
radix: radix.o error.o getoptv.o putoptv.o todigit.o uintspec.o version.o
relate: relate.o depend.o efreopen.o emalloc.o error.o getoptv.o putoptv.o version.o
remove: remove.o charset.o chruesc.o chruescmap.o console.o emalloc.o fgetline.o fputline.o makepath.o mergepath.o regexcomp.o regexfree.o regexhelp.o regexmake.o regexshow.o regexspan.o splitpath.o struesc.o sv_ascii.o todigit.o vfopen.o
rex: rex.o console.o
rexp: rexp.o charset.o chruesc.o emalloc.o error.o getoptv.o putoptv.o regexcomp.o regexfree.o regexmake.o regexshow.o regexspan.o todigit.o version.o
rmpkg: rmpkg.o emalloc.o erealloc.o error.o find.o getoptv.o listcreate.o listdelete.o listdetect.o listexpand.o listinsert.o makefind.o makepath.o match.o mergepath.o partfile.o partpath.o putoptv.o splitpath.o strvercmp.o version.o
runjobs: runjobs.o error.o getoptv.o makefind.o makepath.o match.o mergepath.o partfile.o partpath.o plain.o putoptv.o setumask.o splitpath.o syslog_basic.o syslog_error.o version.o
sbar: sbar.o console.o makepath.o mergepath.o splitpath.o todigit.o uintspec.o vfopen.o
sbrief: sbrief.o error.o escaped.o getoptv.o keep.o literal.o makepath.o mergepath.o peek.o putoptv.o splitpath.o version.o vfopen.o
search: search.o charset.o chruesc.o chruescmap.o console.o efreopen.o emalloc.o fgetline.o find.o fputn.o makefind.o makepath.o match.o mergepath.o partfile.o partpath.o regexcomp.o regexfree.o regexhelp.o regexmake.o regexshow.o regexspan.o showfind.o splitpath.o struesc.o sv_ascii.o todigit.o uintspec.o
setmode: setmode.o atoin.o efopen.o error.o getoptv.o putoptv.o version.o
setnumber: setnumber.o
shakey: shakey.o SHA256Block.o SHA256Fetch.o SHA256Print.o SHA256Reset.o SHA256Write.o error.o getoptv.o putoptv.o version.o
shakeys: shakeys.o SHA256Block.o SHA256Fetch.o SHA256Print.o SHA256Reset.o SHA256Write.o error.o getoptv.o putoptv.o version.o
shout: shout.o broadcast.o emalloc.o error.o getoptv.o putoptv.o syslog_basic.o syslog_error.o version.o
sign: sign.o console.o signf.o todigit.o uintspec.o
single: single.o console.o makepath.o mergepath.o splitpath.o todigit.o uintspec.o vfopen.o
sizeof: sizeof.o
space: space.o chruesc.o console.o escaped.o keep.o literal.o makepath.o mergepath.o peek.o splitpath.o struesc.o todigit.o vfopen.o
srt: srt.o adheap.o console.o deheap.o emalloc.o enheap.o makepath.o mergepath.o reheap.o splitpath.o swap.o todigit.o uintspec.o vfopen.o
stamp: stamp.o
str2hex: str2hex.o
sv: sv.o chrlwr.o chrupr.o console.o efreopen.o fgetline.o indent.o serial.o strcomp.o strconv.o strselect.o todigit.o uintspec.o
sweep: sweep.o error.o getoptv.o makepath.o mergepath.o putoptv.o splitpath.o version.o
symlinks: symlinks.o console.o find.o makefind.o makepath.o match.o mergepath.o partfile.o partpath.o showfind.o splitpath.o
syslog: syslog.o error.o getoptv.o putoptv.o syslog_basic.o syslog_encode.o syslog_facility_codes.o syslog_lookup.o syslog_severity_codes.o version.o
timer: timer.o
tls: tls.o error.o getoptv.o indent.o putoptv.o todigit.o uintspec.o version.o
tr: tr.o charset.o chrset.o chrsub.o chruesc.o error.o getoptv.o makepath.o mergepath.o putoptv.o splitpath.o version.o vfopen.o
trim: trim.o console.o makepath.o mergepath.o splitpath.o todigit.o uintspec.o vfopen.o
try: try.o breakout.o console.o
ts: ts.o
ttcp: ttcp.o
typelist: typelist.o efreopen.o error.o getoptv.o indent.o print.o putoptv.o todigit.o typeload.o typesave.o version.o
undash: undash.o error.o getoptv.o makepath.o mergepath.o putoptv.o splitpath.o version.o vfopen.o
unique: unique.o console.o efreopen.o emalloc.o makepath.o match.o mergepath.o splitpath.o todigit.o uintspec.o
vl: vl.o error.o getoptv.o makepath.o match.o mergepath.o putoptv.o splitpath.o todigit.o uintspec.o version.o vfopen.o
vr: vr.o error.o getoptv.o makepath.o match.o mergepath.o putoptv.o splitpath.o todigit.o uintspec.o version.o vfopen.o
vu: vu.o console.o efreopen.o sv_ascii.o sv_glyph.o
wc: wc.o charset.o chrdef.o chrset.o efreopen.o error.o getoptv.o putoptv.o version.o
what: what.o console.o emalloc.o erealloc.o getviewport.o listcolumn.o listcreate.o listdelete.o listdetect.o listexpand.o listinsert.o strsplit.o todigit.o uintspec.o
whom: whom.o charset.o chruesc.o chruescmap.o console.o emalloc.o erealloc.o getviewport.o listcolumn.o listcreate.o listdelete.o listdetect.o listexpand.o listinsert.o regexcomp.o regexfree.o regexhelp.o regexmake.o regexshow.o regexspan.o sv_ascii.o todigit.o uintspec.o
wl: wl.o charset.o chrdef.o chrlwr.o chrset.o chrupr.o efreopen.o error.o getoptv.o putoptv.o strcomp.o strconv.o version.o
xde: xde.o console.o emalloc.o hexdump.o indent.o reorder.o svindex.o todigit.o uintspec.o xmledit.o xmlfree.o xmlnode.o xmlopen.o xmlsample.o xmlscan.o xmlschema.o
xml: xml.o console.o emalloc.o indent.o reorder.o xmlfree.o xmlindent.o xmlnode.o xmlread.o xmlscan.o xmlstream.o xmltree.o _xmlattribute.o _xmlvalue.o

# ====================================================================
# files;
# --------------------------------------------------------------------

include ../cmassoc/cmassoc.mak
include ../clang/clang.mak
include ../files/files.mak
include ../linux/linux.mak
include ../regex/regex.mak
include ../tools/tools.mak
include ../chrlib/chrlib.mak
include ../strlib/strlib.mak
include ../calc/calc.mak
include ../date/date.mak
include ../link/link.mak
include ../list/list.mak
include ../math/math.mak
include ../sort/sort.mak
include ../tree/tree.mak
include ../scan/scan.mak

