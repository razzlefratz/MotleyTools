#!/bin/bash
# file: set-route.sh
# Published 2004 by Charles Maier Associates Limited for internal use;

# ====================================================================
# add 192.168 gateways 
# --------------------------------------------------------------------

route -A inet add -net 192.168.3.0 gw 66.92.78.242 metric 1
netstat -nr

