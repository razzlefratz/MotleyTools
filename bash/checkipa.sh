#!/bin/bash
# file:
# Published 2004 by Charles Maier Associates Limited for internal use;

# ====================================================================
# extract HOST IP address from /etc/network/interfaces file;
# --------------------------------------------------------------------

ipa=$(mawk "/^[ \\t]*address/ { print \$2 }" /etc/network/interfaces)
ipa=$(echo -n ${ipa})

if [ -z ${ipa} ]; then
	echo "symbol {ipa} is not defined."
        exit 1
fi

# ====================================================================
# define awk/gawk/mawk program body; 
# --------------------------------------------------------------------

action="{ print \"right. \" \$0 \" \" FILENAME; exit (0); } else { print \"wrong! \" \$0; exit (1) \" \" FILENAME; }"
action1="{ if ( \$2 ~ \"${ipa}\"    ) ${action} }"
action2="{ if ( \$2 ~ \"${ipa}:80\" ) ${action} }"

# ====================================================================
# notice 
# --------------------------------------------------------------------
 
echo
echo checking IP addresses ...
echo

# ====================================================================
# search specific files for specific parameters;  
# --------------------------------------------------------------------

gawk "/^[[:blank:]]*BindAddress/ ${action1}" /etc/openssh/ssh_config 
gawk "/^[[:blank:]]*Listen/ ${action1}" /etc/openssh/sshd_config 
gawk "/^[[:blank:]]*Listen/ ${action2}" /etc/apache/httpd.conf
gawk "/^[[:blank:]]*NameVirtualHost/ ${action2}" /etc/apache/httpd.conf 
gawk -F= "/^[[:blank:]]*interfaces/ ${action1}" /etc/samba/smb.conf
gawk -F= "/^[[:blank:]]*listen_address/ ${action1}" /etc/vsftpd/vsftpd.conf

# ====================================================================
# finish 
# --------------------------------------------------------------------
 
echo
echo done.
echo
