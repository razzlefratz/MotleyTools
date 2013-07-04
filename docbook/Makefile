#!/bin/make -f
# file: docbook/Makefile

# ====================================================================
# environment definitions;
# --------------------------------------------------------------------

include ../make.def

DOCBOOK=/usr/share/xml/docbook/stylesheet/docbook-xsl/html

# ====================================================================
# symbols;
# --------------------------------------------------------------------

TRASH=*~ *.[0-9][0-9][0-9] t t.* *.1.html *.c.html *.cpp.html *.h.html *.hpp.html *.7.html *.7a.html *.sh.html *.xml.html *.xsd.html ch[0-9][0-9]*.html *.pdf 
FILES=Makefile *.txt *.xml *.xsl
STYLES=param.xsl lists.xsl synop.xsl
PAGES=cmassoc-tools.xml oascii.xml oethernet.xml oflagword.xml ointerfaces.xml ointerface.xml omemory.xml onumber.xml
IMAGES=
BOOKS=index.html cmassoc-tools.pdf cmassoc-tools.txt

# ====================================================================
# targets;
# --------------------------------------------------------------------

.PHONY: all compile scripts manuals install uninstall clean fresh 

all compile: ${BOOKS} 
	change *.html -e "</html>0" -t "</html>"
	rm *.[0-9][0-9][0-9]
manuals: 
	manuals
scripts:
library:
	su root -c "install -m 0755 -o ${OWNER} -g ${GROUP} -d ${DOC}"
install: library compile 
	su root -c "if [ -d ${DOC} ]; then install -m 0664 -o ${OWNER} -g ${GROUP} *.html *.css *.png ${DOC}; fi"
uninstall:
	su root -c "rm -f ${DOC}/*.c.html ${DOC}/*.h.html ${DOC}/*.7.html"
setup:
	su root -c "install ${STYLES} ${DOCBOOK}"
clean:
	chmod 0755 ${PAGES} ${STYLES}
	rm -f ${TRASH} ${BOOKS}
fresh: clean compile

# ====================================================================
# targets;
# --------------------------------------------------------------------

index.html: ${PAGES}
	xmlto -o . html ${<} 
cmassoc-tools.pdf: ${PAGES} ${IMAGES}
	docbook2pdf ${<}
cmassoc-tools.txt: ${PAGES} 
	xmlto txt ${<}

