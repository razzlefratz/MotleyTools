#!/bin/bash
# file: mailbox.sh
# Publised 2005 by Charles Maier Associates Limited for internal use;

# ===================================================================
#
# -------------------------------------------------------------------

MAILPATH=/var/mail

while [ ${#} != 0 ]; do
        MAILBOX=${MAILPATH}/${1}
	mkdir ${MAILBOX}
	chown ${1}:mail ${MAILBOX}
        chmod 1770 ${MAILBOX}
   	shift
done

# ===================================================================
# finish;
# -------------------------------------------------------------------

echo done.

