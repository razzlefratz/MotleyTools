#!/bin/bash
# file: /etc/default/definitions.sh
# Published 2005 by Charles Maier Associates Limited for internal use;

# ====================================================================
# set {webroot} based on hostname;
# --------------------------------------------------------------------

case ${HOSTNAME} in
ariel|atlas|aries)
	export cdrom=/disk2/ftp/linux
	export build=/home/cmaier/build
	export www=/disk2/www
	;;
appslinux01|appslinux02)
	export cdrom=/home/ftp/linux
	export build=/home/cmaier/build
	export www=/home/www
	;;
*)
	export cdrom=/home/ftp/linux
	export build=/home/cmaier/build
	export www=/home/www
	;;
esac

# ====================================================================
# 
# --------------------------------------------------------------------

export src=${cdrom}/src
export cfg=${cdrom}/etc
export usr=${cdrom}/usr
export tbd=${build}
export hlp=${build}/hlp
export log=${build}/$(basename ${0} .bld).log
export x11=/usr/X11R6
export opt=/usr/local
export alt=/usr/cyrus
unset sys

# ====================================================================
#  
# --------------------------------------------------------------------

PASSWORD=abN/qM.L/H8EQ 
DOCUMENT=${www}/manuals
MAILROOM=/var/mail

