#!/bin/bash
# file: /usr/local/bin/cmassoc/ssh-rsa-perms.sh
# Published 2005 by Charles Maier Associates Limited for internal use;

# ====================================================================
# set permissions on ~/.ssh ssh-rsa files;
# --------------------------------------------------------------------

owner=${USER}:${USER}

if [ -d ~/.ssh ]; then
	chown ${owner} ~/.ssh
	chmod 0700 ~/.ssh
fi

if [ -f ~/.ssh/id_rsa ]; then
	chown ${owner} ~/.ssh/id_rsa
	chmod 0600 ~/.ssh/id_rsa
fi

if [ -f ~/.ssh/authorized_keys ]; then
	chown ${owner} ~/.ssh/authorized_keys
	chmod 0600 ~/.ssh/authorized_keys
fi

if [ -f ~/.ssh/known_hosts ]; then
	chown ${owner} ~/.ssh/known_hosts
	chmod 0600 ~/.ssh/known_hosts
fi

# ====================================================================
#
# --------------------------------------------------------------------

exit 0

