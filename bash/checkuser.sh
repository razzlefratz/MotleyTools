#!/bin/bash
# file:
# Published 2004 by Charles Maier Associates Limited for internal use;

# ====================================================================
# define awk/gawk/mawk program body; 
# --------------------------------------------------------------------

action="{ print \"right. \" \$1 \" \" \$3 \" \" \$4; exit (0); } else { print \"wrong! \" \$1 \" \" \$3 \" \" \$4;  exit (1); }"

# ====================================================================
# search specific files for specific parameters;  
# --------------------------------------------------------------------

echo
echo checking user accounts ...
echo

gawk -F: "/^root/ { if ((\$3 ~ \"0\") && (\$4 ~ \"0\")) ${action} }" /etc/passwd 
gawk -F: "/^daemon/ { if ((\$3 ~ \"1\") && (\$4 ~ \"1\")) ${action} }" /etc/passwd 
gawk -F: "/^bin/ { if ((\$3 ~ \"2\") && (\$4 ~ \"2\")) ${action} }" /etc/passwd 
gawk -F: "/^sys/ { if ((\$3 ~ \"3\") && (\$4 ~ \"3\")) ${action} }" /etc/passwd 
gawk -F: "/^sync/ { if ((\$3 ~ \"4\") && (\$4 ~ \"100\")) ${action} }" /etc/passwd 
gawk -F: "/^games/ { if ((\$3 ~ \"5\") && (\$4 ~ \"100\")) ${action} }" /etc/passwd 
gawk -F: "/^man/ { if ((\$3 ~ \"6\") && (\$4 ~ \"100\")) ${action} }" /etc/passwd 
gawk -F: "/^lp/ { if ((\$3 ~ \"7\") && (\$4 ~ \"7\")) ${action} }" /etc/passwd 
gawk -F: "/^mail/ { if ((\$3 ~ \"8\") && (\$4 ~ \"8\")) ${action} }" /etc/passwd 
gawk -F: "/^news/ { if ((\$3 ~ \"9\") && (\$4 ~ \"9\")) ${action} }" /etc/passwd 
gawk -F: "/^uucp/ { if ((\$3 ~ \"10\") && (\$4 ~ \"10\")) ${action} }" /etc/passwd 
gawk -F: "/^sshd/ { if ((\$3 ~ \"11\") && (\$4 ~ \"11\")) ${action} }" /etc/passwd 
gawk -F: "/^vsftp/ { if ((\$3 ~ \"12\") && (\$4 ~ \"102\")) ${action} }" /etc/passwd 
gawk -F: "/^proxy/ { if ((\$3 ~ \"13\") && (\$4 ~ \"13\")) ${action} }" /etc/passwd 
gawk -F: "/^samba/ { if ((\$3 ~ \"14\") && (\$4 ~ \"102\")) ${action} }" /etc/passwd 
gawk -F: "/^named/ { if ((\$3 ~ \"16\") && (\$4 ~ \"16\")) ${action} }" /etc/passwd 
gawk -F: "/^mysql/ { if ((\$3 ~ \"17\") && (\$4 ~ \"17\")) ${action} }" /etc/passwd 
gawk -F: "/^slapd/ { if ((\$3 ~ \"18\") && (\$4 ~ \"18\")) ${action} }" /etc/passwd 
gawk -F: "/^postgres/ { if ((\$3 ~ \"31\") && (\$4 ~ \"32\")) ${action} }" /etc/passwd 
gawk -F: "/^apache/ { if ((\$3 ~ \"33\") && (\$4 ~ \"33\")) ${action} }" /etc/passwd 
gawk -F: "/^backup/ { if ((\$3 ~ \"34\") && (\$4 ~ \"34\")) ${action} }" /etc/passwd 
gawk -F: "/^operator/ { if ((\$3 ~ \"37\") && (\$4 ~ \"37\")) ${action} }" /etc/passwd 
gawk -F: "/^list/ { if ((\$3 ~ \"38\") && (\$4 ~ \"38\")) ${action} }" /etc/passwd 
gawk -F: "/^irc/ { if ((\$3 ~ \"39\") && (\$4 ~ \"39\")) ${action} }" /etc/passwd 
gawk -F: "/^gnats/ { if ((\$3 ~ \"41\") && (\$4 ~ \"41\")) ${action} }" /etc/passwd 
gawk -F: "/^nobody/ { if ((\$3 ~ \"65534\") && (\$4 ~ \"65534\")) ${action} }" /etc/passwd 
gawk -F: "/^gnome/ { if ((\$3 ~ \"104\") && (\$4 ~ \"104\")) ${action} }" /etc/passwd 
gawk -F: "/^identd/ { if ((\$3 ~ \"100\") && (\$4 ~ \"65535\")) ${action} }" /etc/passwd 
gawk -F: "/^distcc/ { if ((\$3 ~ \"105\") && (\$4 ~ \"1\")) ${action} }" /etc/passwd 
gawk -F: "/^guest/ { if ((\$3 ~ \"100\") && (\$4 ~ \"100\")) ${action} }" /etc/passwd 

