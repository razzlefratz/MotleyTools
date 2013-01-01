# ====================================================================
# date source files;
# --------------------------------------------------------------------

annum.o: annum.c
arctime.o: arctime.c date.h
datecomp.o: datecomp.c date.h
datespec.o: datespec.c tools.h types.h sizes.h
dayofwk.o: dayofwk.c date.h
dayofyr.o: dayofyr.c date.h
daytime.o: daytime.c date.h
encodetime.o: encodetime.c date.h convert.h
endofmo.o: endofmo.c date.h
fridate.o: fridate.c date.h
isleap.o: isleap.c date.h tools.h types.h
logtime.o: logtime.c date.h
logtm.o: logtm.c date.h
midnight.o: midnight.c date.h
mondate.o: mondate.c date.h
month.o: month.c date.h
month2.o: month2.c date.h
months.o: months.c months.h
startofperiod.o: startofperiod.c date.h
strtime.o: strtime.c date.h convert.h
strtm.o: strtm.c date.h convert.h
sv_date1.o: sv_date1.c date.h
sv_date2.o: sv_date2.c date.h
sv_month.o: sv_month.c date.h
sv_wkday.o: sv_wkday.c date.h
timecomp.o: timecomp.c date.h
timespec.o: timespec.c tools.h types.h sizes.h
weekdate.o: weekdate.c date.h
weekdays.o: weekdays.c weekdays.h
workdate.o: workdate.c date.h

# ====================================================================
# date header files;
# --------------------------------------------------------------------

date.h months.h weekdays.h:
	touch ${@}

