# ====================================================================
# ether source files;
# --------------------------------------------------------------------

IPAddr.o: IPAddr.c IPAddr.h
IPAout.o: IPAout.c convert.h
IPDecode.o: IPDecode.c IPAddr.h
IPEncode.o: IPEncode.c IPAddr.h convert.h
IPInAddr.o: IPInAddr.c IPAddr.h
IPString.o: IPString.c IPAddr.h
MACAddr.o: MACAddr.c MACAddr.h MACDecode.c MACEncode.c MACSpec.c
MACAddress.o: MACAddress.c MACDecode.c MACEncode.c MACSpec.c
MACDecode.o: MACDecode.c MACAddr.h
MACEncode.o: MACEncode.c MACAddr.h
MACSpec.o: MACSpec.c MACAddr.h error.h
OUIName.o: OUIName.c tools.h
bind_ll.o: bind_ll.c packet_ll.h error.h
channel.o: channel.c open_ll.c recvfrom_ll.c sendto_ll.c
channelout.o: channelout.c channel.h error.h memory.h types.h
getIPv4.o: getIPv4.c IPAddr.h
isIPv4.o: isIPv4.c IPAddr.h types.h
open_ll.o: open_ll.c channel.h error.h
recvfrom_ll.o: recvfrom_ll.c channel.h error.h memory.h
sendto_ll.o: sendto_ll.c channel.h error.h memory.h
sockaddrout.o: sockaddrout.c channel.h

# ====================================================================
# ether header files;
# --------------------------------------------------------------------

IPAddr.h: IPAddr.h types.h
	touch ../ether/${@}
channel.h: channel.h types.h
	touch ../ether/${@}
MACAddr.h: MACAddr.h types.h
	touch ../ether/${@}
packet_ll.h: packet_ll.h types.h
	touch ../ether/${@}

