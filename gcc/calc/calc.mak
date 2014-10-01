# ====================================================================
# calc source files;
# --------------------------------------------------------------------

dpow.o: dpow.c calc.h
dscale.o: dscale.c print.h
dtoa.o: dtoa.c calc.h
dtos.o: dtos.c print.h
gcd.o: gcd.c calc.h
iabs.o: iabs.c calc.h
ifact.o: ifact.c calc.h
ipow.o: ipow.c calc.h
iscale.o: iscale.c calc.h print.h
isgn.o: isgn.c calc.h
lcm.o: lcm.c calc.h
logn.o: logn.c calc.h
nblock.o: nblock.c calc.h
pfact.o: pfact.c calc.h
pmod.o: pmod.c calc.h
qmod.o: qmod.c calc.h
range.o: range.c calc.h
smooth.o: smooth.c calc.h

# ====================================================================
# calc header files;
# --------------------------------------------------------------------

calc.h:
	touch ../calc/${@}

