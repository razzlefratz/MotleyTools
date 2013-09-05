#!/bin/bash
# file: build.sh  
# Published 2004 by Charles Maier Associates Limited for internal use;

# ======================================================================
# define default logfile if undefined; 
# ----------------------------------------------------------------------

if [ -z ${log} ]; then
	log=${tbd}/build.log
fi

# ======================================================================
# record start of build;
# ----------------------------------------------------------------------

echo $(date) ${1} ${2} ${3} | tee -a ${log}

# ======================================================================
# folders and files must be defined and must exist;
# ----------------------------------------------------------------------

if [ -z $PKG_CONFIG_PATH ]; then 
	echo symbol PKG_CONFIG_PATH is not defined | tee -a ${log}
	exit 1
elif [ -z $LD_LIBRARY_PATH ]; then 
	echo symbol LD_LIBRARY_PATH is not defined | tee -a ${log}
	exit 1
elif [ -z ${tbd} ]; then 
	echo symbol {tbd} is not defined | tee -a ${log}
	exit 1
elif [ -z ${src} ]; then
	echo symbol {src} is not defined | tee -a ${log}
	exit 1
elif [ -z ${hlp} ]; then
	echo symbol {hlp} is not defined | tee -a ${log}
	exit 1
elif [ ! -d ${tbd} ]; then
	echo folder ${tbd} does not exist | tee -a ${log}
	exit 1
elif [ ! -d ${src} ]; then
	echo folder ${src} does not exist | tee -a ${log}
	exit 1
elif [ ! -d ${hlp} ]; then
	echo folder ${hlp} does not exist | tee -a ${log}
	exit 1
elif [ -z ${1} ]; then 
	echo install root is not defined | tee -a ${log}
	exit 1
elif [ ! -d ${1} ]; then
	echo folder ${1} does not exist | tee -a ${log}
	exit 1
elif [ -z ${2} ]; then 
	echo package name is not defined | tee -a ${log}
	exit 1 
elif [ -d ${tbd}/${2} ]; then
	echo package ${2} already unpacked .
elif [ -f ${src}/${2}.tar ]; then
	tar -vxf ${src}/${2}.tar
elif [ -f ${src}/${2}.tgz ]; then
	tar -vzxf -C ${tbd} ${src}/${2}.tgz
elif [ -f ${src}/${2}.tar.gz ]; then
	tar -vzxf -C ${tbd} ${src}/${2}.tar.gz
elif [ -f ${src}/${2}.tar.tar ]; then
	tar -vjxf -C ${tbd} ${src}/${2}.tar.tar 
elif [ -f ${src}/${2}.tar.bz2 ]; then
	tar -vjxf -C ${tbd} ${src}/${2}.tar.bz2
elif [ -f ${src}/${2}.* ]; then
	echo package ${2} may have wrong extension | tee -a ${log}
 	exit 1
else
	echo package ${2} does not exist | tee -a ${log}
 	exit 1
fi
 
# ======================================================================
# confirm that archive unpacked and folder by same name exists; 
# ----------------------------------------------------------------------

if [ ! -d ${tbd}/${2} ]; then
	echo folder ${tbd}/${2} is missing | tee -a ${log}
	echo external and interal names may differ
	exit 1
else
	chown -R samba:smb ${tbd}/${2} 
	cd ${tbd}/${2}
fi

# ======================================================================
# force standard ${execute} and ${support} prefixes; 
# ----------------------------------------------------------------------

if [ -z ${1} ]; then
	echo install root not defined | tee -a ${log}
	exit 1	
elif [ ${1} == "/" ]; then
	execute="" 
	support=/usr 
elif [ ${1} == "/usr" ]; then
	execute=${1} 
	support=${1} 
elif [ ${1} == "/usr/local" ]; then
	execute=${1} 
	support=${1} 
elif [ ${1} == "/usr/X11R6" ]; then
	execute=${1} 
	support=${1} 
elif [ ${1} == "/usr/gnome" ]; then
	execute=${1} 
	support=${1} 
else
	execute=${1} 
	support=${1} 
fi

# ======================================================================
# produce help file for reference;
# ----------------------------------------------------------------------

${tbd}/${2}/configure \
	--help \
	> ${hlp}/${2}.help 

# ======================================================================
# configure package build stream;
# ----------------------------------------------------------------------

${tbd}/${2}/configure \
	--prefix=${support} \
	--exec-prefix=${execute} \
	--bindir=${execute}/bin \
	--sbindir=${execute}/sbin \
	--libdir=${execute}/lib \
	--libexecdir=${execute}/sbin \
	--sysconfdir=${execute}/etc \
	--includedir=${support}/include \
	--datadir=${support}/share \
	--mandir=${support}/share/man \
	--infodir=${support}/share/info \
	--localstatedir=${execute}/var/run \
	--enable-shared \
	--enable-static \
	--disable-gtk-doc \
	--disable-nls \
	--with-gnu-ld \
	--with-x \
	${4} \
	${5} \
	${6} \
	${7} \
	${8} \
	${9}

# ======================================================================
# make and install package; 
# ----------------------------------------------------------------------

make
make install

# ======================================================================
# report completion status;
# ----------------------------------------------------------------------

if [ -f ${tbd}/${2}/config.log ]; then 
	tail -1 ${tbd}/${2}/config.log | tee -a ${log} 
else 
	echo no log file | tee -a ${log} 
fi

# ======================================================================
# cleanup; 
# ----------------------------------------------------------------------

cd ${tbd}
rm -r ${tbd}/${2}
ldconfig

# ======================================================================
# expand   
# ----------------------------------------------------------------------

cat >> build.txt <<EOF 
# ====================================================================
# ${2}
# --------------------------------------------------------------------

pkg=${2}
echo \$(date) \${pkg} >> \${log}
rm -fr \${tbd}/\${pkg}
rm -fr \${tbd}/\${pkg}.orig
tar -vjxf \${src}/\${pkg}.tar.bz2
mv \${pkg}/\${pkg} \${tbd}/\${pkg}.orig
tar -vjxf \${src}/\${pkg}.tar.bz2
if [ ! -d \${tbd}/\${pkg} ]; then
	echo unpack failed >> \${log}
fi
cd \${tbd}/\${pkg}
configure --help > \${hlp}/\${pkg}.help 
\${tbd}/\${pkg}/configure \\
	--prefix=\${lfs} \\
	--exec-prefix=\${lfs} \\
	--bindir=\${lfs}/bin \\
	--sbindir=\${lfs}/sbin \\
	--libdir=\${lfs}/lib \\
	--libexecdir=\${lfs}/sbin \\
	--sysconfdir=\${lfs}/etc \\
	--includedir=\${lfs}/include \\
	--datadir=\${lfs}/share \\
	--mandir=\${lfs}/share/man \\
	--infodir=\${lfs}/share/info \\
	--localstatedir=/var/run \\
	--enable-shared \\
	--enable-static \\
	--with-gnu-ld \\
	--with-x
make
make install 
if [ -f config.log ]; then 
	tail -1 config.log | tee -a \${log} 
else 
	echo no log file | tee -a \${log} 
fi
cd \${tbd}
rm -fr \${tbd}/\${pkg}.orig
rm -fr \${tbd}/\${pkg}
ldconfig

EOF

# ======================================================================
# return exit code;
# ----------------------------------------------------------------------

exit 0

