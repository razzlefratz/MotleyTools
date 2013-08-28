#!/bin/bash
# file: /etc/default/environment.sh
# Published 2005 by Charles Maier Associates Limited for internal use;

# ====================================================================
# verifications; 
# --------------------------------------------------------------------

if [ ! -f /etc/debian_version ]; then
	echo ${0}: this is not a debian installation.
 	exit 1
elif [ -z ${PKG_CONFIG} ]; then
	echo ${0}: symbol PKG_CONFIG is undefined.
	exit 1
elif [ -z ${PKG_CONFIG_PATH} ]; then
	echo ${0}: symbol PKG_CONFIG_PATH is undefined.
	exit 1
elif [ -z ${LD_LIBRARY_PATH} ]; then
	echo ${0}: symbol LD_LIBRARY_PATH is undefined.
	exit 1
 
# ====================================================================
# confirm that selected symbols are not undefined.;  
# --------------------------------------------------------------------

elif [ -z ${CMTOOLS} ]; then
	echo ${0}: symbol CMTOOLS is undefined.
	exit 1
elif [ -z ${CMADMIN} ]; then
	echo ${0}: symbol CMADMIN is undefined.
	exit 1

# ====================================================================
# confirm that selected symbols are not undefined.;  
# --------------------------------------------------------------------

elif [ ! -z ${sys} ]; then
	echo ${0}: symbol {sys} should not be defined.
	exit 1
elif [ -z ${tbd} ]; then
	echo ${0}: symbol {tbd} is undefined.
	exit 1
elif [ -z ${cfg} ]; then
	echo ${0}: symbol {cfg} is undefined.
	exit 1
elif [ -z ${src} ]; then
	echo ${0}: symbol {src} is undefined.
	exit 1
elif [ -z ${hlp} ]; then
	echo ${0}: symbol {hlp} is undefined.
	exit 1
elif [ -z ${log} ]; then
	echo ${0}: symbol {log} is undefined.
	exit 1

# ====================================================================
# confirm that selected symbols reference valid folders; 
# --------------------------------------------------------------------

elif [ ! -d ${src} ]; then
	echo ${0}: folder ${src} does not exist
	exit 1
elif [ ! -d ${cfg} ]; then
	echo ${0}: folder ${cfg} does not exist
	exit 1
elif [ ! -d ${tbd} ]; then
	echo ${0}: folder ${tbd} does not exist
	exit 1
elif [ ! -d ${hlp} ]; then
	echo ${0}: folder ${hlp} does not exist
	exit 1

# ====================================================================
# confirm that selected CMLinux symlinks exist;   
# --------------------------------------------------------------------

elif [ ! /libexec -ef /sbin ]; then
	echo ${0}: folder /libexec is not linked to /sbin.
	exit 1
elif [ ! /man -ef /share/man ]; then
	echo ${0}: folder /man is not linked to /share/man.
	exit 1
elif [ ! /doc -ef ${sys}/share/doc ]; then
	echo ${0}: folder /doc is not linked to /share/doc.
	exit 1
elif [ ! /info -ef ${sys}/share/info ]; then
	echo ${0}: folder /info is not linked to /share/info.
	exit 1

elif [ ! /usr/etc -ef /etc ]; then
	echo ${0}: folder /usr/etc is not linked to /etc.
	exit 1
elif [ ! /usr/libexec -ef /usr/sbin ]; then
	echo ${0}: folder /usr/libexec is not linked to /usr/sbin.
	exit 1
elif [ ! /usr/man -ef /usr/share/man ]; then
	echo ${0}: folder /usr/man is not linked to /usr/share/man.
	exit 1
elif [ ! /usr/doc -ef /usr/share/doc ]; then
	echo ${0}: folder /usr/doc is not linked to /usr/share/doc.
	exit 1
elif [ ! /usr/info -ef /usr/share/info ]; then
	echo ${0}: folder /usr/doc is not linked to /usr/share/doc.
	exit 1
elif [ ! /usr/var -ef /var ]; then
	echo ${0}: folder /usr/var is not linked to /var.
	exit 1

elif [ ! /usr/local/etc -ef /usr/etc ]; then
	echo ${0}: folder /usr/local/etc is not linked to /usr/etc.
	exit 1
elif [ ! /usr/local/libexec -ef /usr/local/sbin ]; then
	echo ${0}: folder /usr/local/libexec is not linked to /usr/local/sbin.
	exit 1
elif [ ! /usr/local/man -ef /usr/local/share/man ]; then
	echo ${0}: folder /usr/local/man is not linked to /usr/local/share/man.
	exit 1
elif [ ! /usr/local/doc -ef /usr/local/share/doc ]; then
	echo ${0}: folder /usr/local/doc is not linked to /usr/local/share/doc.
	exit 1
elif [ ! /usr/local/info -ef /usr/local/share/info ]; then
	echo ${0}: folder /usr/local/info is not linked to /usr/local/share/info.
	exit 1
elif [ ! /usr/local/var -ef /usr/var ]; then
	echo ${0}: folder /usr/local/var is not linked to /usr/var.
	exit 1
fi

# ====================================================================
# checks passed;  
# --------------------------------------------------------------------

rm -f ${log}
if [ ]; then
	echo PATH=${PATH} >> ${log}
	echo {sys}=${sys} >> ${log}
	echo {opt}=${opt} >> ${log}
	echo {tbd}=${tbd} >> ${log}
	echo {cfg}=${cfg} >> ${log}
	echo {src}=${src} >> ${log}
	echo {hlp}=${hlp} >> ${log}
	echo {log}=${log} >> ${log}
fi

