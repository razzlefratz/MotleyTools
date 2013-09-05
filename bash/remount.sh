#!/bin/bash
# file: /root/remount.sh
# Published 2005 by Charles Maier Associates Limited for internal use;

# ===================================================================
#
# -------------------------------------------------------------------

mount -t ext2 /dev/sda1 / -o remount,rw
mount -t ext2 /dev/sda2 /usr -o remount,rw
mount -t ext2 /dev/sda3 /var -o remount,rw
mount -t ext2 /dev/sdb1 /home -o remount,rw

# ===================================================================
#
# -------------------------------------------------------------------

echo done.

