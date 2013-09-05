#!/bin/bash
# file: /usr/local/bin/cmassoc/bridge.sh

# ====================================================================
#
# --------------------------------------------------------------------

BRIDGE=${HOSTNAME}
BRIDGE=bridge
FOLDER=/proc/sys/net/bridge
DEVICE1=eth1
DEVICE2=plc1
DEVICE2=plc0

# ====================================================================
#
# --------------------------------------------------------------------

case ${1} in

start)
	ifconfig ${DEVICE1} 0.0.0.0
	ifconfig ${DEVICE2} 0.0.0.0
	brctl addbr ${BRIDGE}
	brctl addif ${BRIDGE} ${DEVICE1}
	brctl addif ${BRIDGE} ${DEVICE2}
	for file in ${FOLDER}/*; do echo 0 > ${file}; done
	ifconfig ${BRIDGE} up
	;;
stop)
	ifconfig ${BRIDGE} down
	for file in ${FOLDER}/*; do echo 1 > ${file}; done
	brctl delif ${BRIDGE} ${DEVICE1}
	brctl delif ${BRIDGE} ${DEVICE2}
	brctl delbr ${BRIDGE}
	ifconfig ${DEVICE1} down     
	ifconfig ${DEVICE2} down      
	;;
restart)
	${0} stop
	sleep 2
	${0} start
	;;
show)
	brctl showstp ${BRIDGE}
	;;
*)
	echo "$(basename ${0}) [ start | stop | restart ]"
	;;
esac

# ====================================================================
#
# --------------------------------------------------------------------

exit ${?}

