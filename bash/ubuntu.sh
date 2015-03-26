#!/bin/bash
# file: /root/ubuntu.sh

# ====================================================================
# symbols;
# --------------------------------------------------------------------

KERNEL=$(uname -r)
OWNER=cmaier
GROUP=qsdk

# ====================================================================
#
# --------------------------------------------------------------------

cat > /etc/environment.sh << EOF
PATH="/usr/local/sbin:/usr/local/bin:/usr/sbin:/usr/bin:/sbin:/bin:/usr/games:/usr/local/bin/cmassoc:~:.
EOF

# ====================================================================
#
# --------------------------------------------------------------------

cat > ~/.exrc << EOF
set number
EOF

# ====================================================================
#
# --------------------------------------------------------------------

install -m 0755 -o ${OWNER} -g ${GROUP} -d ${BLDROOT}

# ====================================================================
#
# --------------------------------------------------------------------

apt-get update
apt-get remove openoffice.org-impress openoffice.org-writer openoffice.org-calc openoffice-base gnome-games
apt-get install gnome codeblocks bluefish vlc
apt-get install libcurl4-gnutls-dev libexpat1-dev gettext libz-dev libssl-dev
apt-get install gcc g++ make git cgit nvi bvi rsync
apt-get install docbook docbook-xml docbook-dsssl docbook-xsl dblatex xsltproc xmlto
apt-get install openssh-server vsftpd apache2 mysql-server-5.0 php5-mysql samba
apt-get install wireshark tshark bridge-utils

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

