#!/bin/bash
# file: /etc/default/machinename.sh
# Published 2005 by Charles Maier Associates Limited for internal use;

# ====================================================================
# configure local host and domain names;
# --------------------------------------------------------------------

machine=${HOSTNAME}
network=cmassoc.net

echo -n "\nenter machine name [${machine}]: "
read
if [ -z ${REPLY} ]; then
	machine=${REPLY}
fi

echo -n "\nenter network name [${network}]: "
read 
if [ -z ${REPLY} ]; then
	network=${REPLY}
fi

cat > /etc/sysctl.conf << EOF
# file: /etc/sysctl.conf
# Published 2005 by Charles Maier Associates Limited for internal use;

# ====================================================================
# define hostname and domainname;
# --------------------------------------------------------------------

kernel.hostname = ${machine}
kernel.domainname = ${network}
EOF

# ====================================================================
# synchronize /etc/hostname with the kernel 
# --------------------------------------------------------------------

rm -f /etc/hostname
ln -fs /proc/sys/kernel/hostname /etc/hostname
rm -f /etc/rcS.d/[KS][0-9][0-9]hostname.sh
rm -f /etc/init.d/hostname.sh

# ====================================================================
# replace /etc/localtime files with symlink;
# --------------------------------------------------------------------

ln -fs /usr/share/zoneinfo/US/Eastern /etc/localtime

