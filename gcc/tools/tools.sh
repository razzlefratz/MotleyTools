#!/bin/bash
# file: tools/tools.sh

# ====================================================================
#
# --------------------------------------------------------------------

gcc -Wall -Wextra -Wno-unused-parameter -c alert.c
gcc -Wall -Wextra -Wno-unused-parameter -c arith.c
gcc -Wall -Wextra -Wno-unused-parameter -c assist.c
gcc -Wall -Wextra -Wno-unused-parameter -c synonym.c
gcc -Wall -Wextra -Wno-unused-parameter -c synonyms.c
gcc -Wall -Wextra -Wno-unused-parameter -c argv2str.c
gcc -Wall -Wextra -Wno-unused-parameter -c atoin.c
gcc -Wall -Wextra -Wno-unused-parameter -c b64dump.c
gcc -Wall -Wextra -Wno-unused-parameter -c basespec.c
gcc -Wall -Wextra -Wno-unused-parameter -c binencode.c
gcc -Wall -Wextra -Wno-unused-parameter -c bindecode.c
gcc -Wall -Wextra -Wno-unused-parameter -c bindump.c
gcc -Wall -Wextra -Wno-unused-parameter -c binout.c
gcc -Wall -Wextra -Wno-unused-parameter -c breakout.c
gcc -Wall -Wextra -Wno-unused-parameter -c bswap16.c
gcc -Wall -Wextra -Wno-unused-parameter -c bswap32.c
gcc -Wall -Wextra -Wno-unused-parameter -c bytespec.c
gcc -Wall -Wextra -Wno-unused-parameter -c chrout.c
gcc -Wall -Wextra -Wno-unused-parameter -c center.c
gcc -Wall -Wextra -Wno-unused-parameter -c cgetc.c
gcc -Wall -Wextra -Wno-unused-parameter -c checksum16.c
gcc -Wall -Wextra -Wno-unused-parameter -c checksum32.c
gcc -Wall -Wextra -Wno-unused-parameter -c clr32bitmap.c
gcc -Wall -Wextra -Wno-unused-parameter -c codeload.c
gcc -Wall -Wextra -Wno-unused-parameter -c codelist.c
gcc -Wall -Wextra -Wno-unused-parameter -c codename.c
gcc -Wall -Wextra -Wno-unused-parameter -c codesave.c
gcc -Wall -Wextra -Wno-unused-parameter -c dcl.c
gcc -Wall -Wextra -Wno-unused-parameter -c dcl.chr.c
gcc -Wall -Wextra -Wno-unused-parameter -c dcl.str.c
gcc -Wall -Wextra -Wno-unused-parameter -c config.c
gcc -Wall -Wextra -Wno-unused-parameter -c cread.c
gcc -Wall -Wextra -Wno-unused-parameter -c cwrite.c
gcc -Wall -Wextra -Wno-unused-parameter -c dataspec.c
gcc -Wall -Wextra -Wno-unused-parameter -c debug.c
gcc -Wall -Wextra -Wno-unused-parameter -c decdecode.c
gcc -Wall -Wextra -Wno-unused-parameter -c decencode.c
gcc -Wall -Wextra -Wno-unused-parameter -c decout.c
gcc -Wall -Wextra -Wno-unused-parameter -c dehex.c
gcc -Wall -Wextra -Wno-unused-parameter -c efopen.c
gcc -Wall -Wextra -Wno-unused-parameter -c efreopen.c
gcc -Wall -Wextra -Wno-unused-parameter -c emalloc.c
gcc -Wall -Wextra -Wno-unused-parameter -c enhex.c
gcc -Wall -Wextra -Wno-unused-parameter -c eperror.c
gcc -Wall -Wextra -Wno-unused-parameter -c eprintf.c
gcc -Wall -Wextra -Wno-unused-parameter -c equate.c
gcc -Wall -Wextra -Wno-unused-parameter -c erealloc.c
gcc -Wall -Wextra -Wno-unused-parameter -c error.c
gcc -Wall -Wextra -Wno-unused-parameter -c error_on_line.c
gcc -Wall -Wextra -Wno-unused-parameter -c event.c
gcc -Wall -Wextra -Wno-unused-parameter -c fdchecksum16.c
gcc -Wall -Wextra -Wno-unused-parameter -c fdchecksum32.c
gcc -Wall -Wextra -Wno-unused-parameter -c fdgetc.c
gcc -Wall -Wextra -Wno-unused-parameter -c fdputc.c
gcc -Wall -Wextra -Wno-unused-parameter -c fgetline.c
gcc -Wall -Wextra -Wno-unused-parameter -c fgetlongline.c
gcc -Wall -Wextra -Wno-unused-parameter -c fgetshortline.c
gcc -Wall -Wextra -Wno-unused-parameter -c fgetv.c
gcc -Wall -Wextra -Wno-unused-parameter -c fprintv.c
gcc -Wall -Wextra -Wno-unused-parameter -c fputline.c
gcc -Wall -Wextra -Wno-unused-parameter -c fputn.c
gcc -Wall -Wextra -Wno-unused-parameter -c fputv.c
gcc -Wall -Wextra -Wno-unused-parameter -c fvalue.c
gcc -Wall -Wextra -Wno-unused-parameter -c gather.c
gcc -Wall -Wextra -Wno-unused-parameter -c getch.c
# gcc -Wall -Wextra -Wno-unused-parameter -c getopt.c
# gcc -Wall -Wextra -Wno-unused-parameter -c getopt1.c
gcc -Wall -Wextra -Wno-unused-parameter -c getargv.c
gcc -Wall -Wextra -Wno-unused-parameter -c getfields.c
gcc -Wall -Wextra -Wno-unused-parameter -c getoptv.c
gcc -Wall -Wextra -Wno-unused-parameter -c getst.c
gcc -Wall -Wextra -Wno-unused-parameter -c getvalue.c
gcc -Wall -Wextra -Wno-unused-parameter -c help.c
gcc -Wall -Wextra -Wno-unused-parameter -c hexdecode.c
gcc -Wall -Wextra -Wno-unused-parameter -c hexdump.c
gcc -Wall -Wextra -Wno-unused-parameter -c hexencode.c
gcc -Wall -Wextra -Wno-unused-parameter -c hexload.c
gcc -Wall -Wextra -Wno-unused-parameter -c hexoffset.c
gcc -Wall -Wextra -Wno-unused-parameter -c hexout.c
gcc -Wall -Wextra -Wno-unused-parameter -c hexread.c
gcc -Wall -Wextra -Wno-unused-parameter -c hexstring.c
gcc -Wall -Wextra -Wno-unused-parameter -c hexwrite.c
gcc -Wall -Wextra -Wno-unused-parameter -c hexview.c
# gcc -Wall -Wextra -Wno-unused-parameter -c hostspec.c
gcc -Wall -Wextra -Wno-unused-parameter -c ietfdecode.c
gcc -Wall -Wextra -Wno-unused-parameter -c ietfencode.c
gcc -Wall -Wextra -Wno-unused-parameter -c ipv4spec.c
gcc -Wall -Wextra -Wno-unused-parameter -c ipv6spec.c
gcc -Wall -Wextra -Wno-unused-parameter -c itoan.c
gcc -Wall -Wextra -Wno-unused-parameter -c itoax.c
gcc -Wall -Wextra -Wno-unused-parameter -c itosm.c
gcc -Wall -Wextra -Wno-unused-parameter -c itosn.c
gcc -Wall -Wextra -Wno-unused-parameter -c lookup.c
gcc -Wall -Wextra -Wno-unused-parameter -c markup.c
gcc -Wall -Wextra -Wno-unused-parameter -c memdecr.c
gcc -Wall -Wextra -Wno-unused-parameter -c memencode.c
gcc -Wall -Wextra -Wno-unused-parameter -c memfold.c
gcc -Wall -Wextra -Wno-unused-parameter -c memincr.c
gcc -Wall -Wextra -Wno-unused-parameter -c memout.c
gcc -Wall -Wextra -Wno-unused-parameter -c memswap.c
gcc -Wall -Wextra -Wno-unused-parameter -c memwrap.c
gcc -Wall -Wextra -Wno-unused-parameter -c modespec.c
gcc -Wall -Wextra -Wno-unused-parameter -c more.c
gcc -Wall -Wextra -Wno-unused-parameter -c namecode.c
gcc -Wall -Wextra -Wno-unused-parameter -c nametype.c
gcc -Wall -Wextra -Wno-unused-parameter -c page.c
gcc -Wall -Wextra -Wno-unused-parameter -c print.c
gcc -Wall -Wextra -Wno-unused-parameter -c printb.c
gcc -Wall -Wextra -Wno-unused-parameter -c printd.c
gcc -Wall -Wextra -Wno-unused-parameter -c printn.c
gcc -Wall -Wextra -Wno-unused-parameter -c printv.c
gcc -Wall -Wextra -Wno-unused-parameter -c printx.c
gcc -Wall -Wextra -Wno-unused-parameter -c profile.c
# gcc -Wall -Wextra -Wno-unused-parameter -c putopt.c
gcc -Wall -Wextra -Wno-unused-parameter -c putoptv.c
gcc -Wall -Wextra -Wno-unused-parameter -c readtoken.c
gcc -Wall -Wextra -Wno-unused-parameter -c regview.c
gcc -Wall -Wextra -Wno-unused-parameter -c reverse.c
gcc -Wall -Wextra -Wno-unused-parameter -c scatter.c
gcc -Wall -Wextra -Wno-unused-parameter -c serial.c
gcc -Wall -Wextra -Wno-unused-parameter -c set32bitmap.c
gcc -Wall -Wextra -Wno-unused-parameter -c setinfo.c
gcc -Wall -Wextra -Wno-unused-parameter -c signf.c
gcc -Wall -Wextra -Wno-unused-parameter -c sintspec.c
gcc -Wall -Wextra -Wno-unused-parameter -c sockspec.c
gcc -Wall -Wextra -Wno-unused-parameter -c statement.c
gcc -Wall -Wextra -Wno-unused-parameter -c strdecr.c
gcc -Wall -Wextra -Wno-unused-parameter -c strincr.c
gcc -Wall -Wextra -Wno-unused-parameter -c symbol.c
# gcc -Wall -Wextra -Wno-unused-parameter -c symbols.c
gcc -Wall -Wextra -Wno-unused-parameter -c tabrule.c
gcc -Wall -Wextra -Wno-unused-parameter -c tabs.c
gcc -Wall -Wextra -Wno-unused-parameter -c tabspec.c
gcc -Wall -Wextra -Wno-unused-parameter -c termspec.c
gcc -Wall -Wextra -Wno-unused-parameter -c todigit.c
gcc -Wall -Wextra -Wno-unused-parameter -c token.c
gcc -Wall -Wextra -Wno-unused-parameter -c trace.c
gcc -Wall -Wextra -Wno-unused-parameter -c totruth.c
gcc -Wall -Wextra -Wno-unused-parameter -c typeload.c
gcc -Wall -Wextra -Wno-unused-parameter -c typelist.c
gcc -Wall -Wextra -Wno-unused-parameter -c typename.c
gcc -Wall -Wextra -Wno-unused-parameter -c typesave.c
gcc -Wall -Wextra -Wno-unused-parameter -c uintspec.c
gcc -Wall -Wextra -Wno-unused-parameter -c unixdecode.c
gcc -Wall -Wextra -Wno-unused-parameter -c unixencode.c
gcc -Wall -Wextra -Wno-unused-parameter -c version.c

# ====================================================================
#
# --------------------------------------------------------------------

rm -f *.o

