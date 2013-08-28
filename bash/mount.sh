#!/bin/bash
# file: /root/mount.sh
# Published 2005 by Charles Maier Associates Limited for internal use;

# ===================================================================
#
# -------------------------------------------------------------------

mount /dev/sda1 / -o remount,rw
mount /dev/sda2 /usr -w
mount /dev/sda3 /var -w
mount /dev/sdb1 /home -w

# ===================================================================
#
# -------------------------------------------------------------------

done.

