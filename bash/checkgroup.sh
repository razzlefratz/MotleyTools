#!/bin/bash
# file:
# Published 2004 by Charles Maier Associates Limited for internal use;

# ====================================================================
# define awk/gawk/mawk program body; 
# --------------------------------------------------------------------

action="{ print \"right. \" \$1 \" \" \$3; exit (0); } else { print \"wrong! \" \$1 \" \" \$3;  exit (1); }"

# ====================================================================
# search specific files for specific parameters;  
# --------------------------------------------------------------------

echo
echo checking user groups ...
echo

gawk -F: "/^ssh/ { if ( \$3 ~ \"11\" ) ${action} }" /etc/group 
gawk -F: "/^ftp/ { if ( \$3 ~ \"12\" ) ${action} }" /etc/group 
gawk -F: "/^smb/ { if ( \$3 ~ \"14\" ) ${action} }" /etc/group 
gawk -F: "/^dns/ { if ( \$3 ~ \"16\" ) ${action} }" /etc/group 
gawk -F: "/^sql/ { if ( \$3 ~ \"17\" ) ${action} }" /etc/group 
gawk -F: "/^ldap/ { if ( \$3 ~ \"18\" ) ${action} }" /etc/group 
gawk -F: "/^www/ { if ( \$3 ~ \"33\" ) ${action} }" /etc/group 
gawk -F: "/^hosts/ { if ( \$3 ~ \"101\" ) ${action} }" /etc/group 
gawk -F: "/^share/ { if ( \$3 ~ \"102\" ) ${action} }" /etc/group 
gawk -F: "/^guest/ { if ( \$3 ~ \"103\" ) ${action} }" /etc/group 
gawk -F: "/^gnome/ { if ( \$3 ~ \"104\" ) ${action} }" /etc/group 

# ====================================================================
# search specific files for specific parameters;  
# --------------------------------------------------------------------

gawk -F: "/^sshd/ { if ((\$3 ~ \"11\") && (\$4 ~ \"11\")) ${action} }" /etc/passwd 
gawk -F: "/^vsftp/ { if ((\$3 ~ \"12\") && (\$4 ~ \"102\")) ${action} }" /etc/passwd 
