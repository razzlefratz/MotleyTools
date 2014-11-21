#!/bin/bash
# file: /root/ubuntu.sh

# ====================================================================
# symbols;
# --------------------------------------------------------------------

KERNEL=$(uname -r)
CVSROOT="cmaier@appslinux01.intellon.com:/home/cvs"
BLDROOT="/home/cmaier/build"
P4ROOT=/home/cmaier/build/Apps/Software

# ====================================================================
#
# --------------------------------------------------------------------

install -m 0755 -o root -g root -d ${CVSROOT} ${BLDROOT} ${P4ROOT}

# ====================================================================
#
# --------------------------------------------------------------------

apt-get update
apt-get remove openoffice.org-impress openoffice.org-writer openoffice.org-calc openoffice-base gnome-games
apt-get install libcurl4-gnutls-dev libexpat1-dev gettext libz-dev libssl-dev
apt-get install codeblocks bluefish
apt-get install docbook docbook-xml docbook-dsssl docbook-xsl dblatex xsltproc xmlto
apt-get install vsftpd apache2 mysql-server-5.0 php5-mysql 
apt-get install openssh-server samba rsync 
apt-get install irssi
apt-get install gcc g++ git cvs nvi bvi cgit
apt-get install wireshark tshark 
apt-get install bridge-utils
apt-get install vlc

# ====================================================================
#
# --------------------------------------------------------------------

if [ ]; then
	install -m 0755 -o root -g root -d /etc/eclipse
	echo /usr/lib/jvm/java-6-sun-1.6.0.00 > /etc/eclipse/java_home
	apt-get install eclipse eclipse-cdt free-java-sdk
fi
	
# ====================================================================
#
# --------------------------------------------------------------------

if [ ]; then
	apt-get install kernel-package libncurses5-dev fakeroot initrd-tools
	ln -fs /usr/src/linux-headers-${KERNEL} /lib/modules/${KERNEL}/source
fi

# ====================================================================
#
# --------------------------------------------------------------------

cat > /etc/environment << EOF
PATH=${PATH}:/usr/local/bin/cmassoc:.
CVSROOT="cmaier@appslunix01.intellon.com:/home/cvs"
EOF

