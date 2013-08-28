#!/bin/bash
# file: linux/system.bld 
# Published 2004 by Charles Maier Associates Limited for internal use;

# install CMLinux configuration folders
install -m 0755 -o root -g root -d /etc/cron
install -m 0755 -o root -g root -d /etc/cron/daily
if [ ! /etc/cron.daily -ef /etc/cron/daily ]; then
	echo ... created /etc/cron/daily folder >> ${log}
	cp -fr /etc/cron.daily/* /etc/cron/daily/
        rm -fr /etc/cron.daily
        ln -fs /etc/cron/daily /etc/cron.daily
fi
install -m 0755 -o root -g root -d /etc/cron/weekly
if [ ! /etc/cron.weekly -ef /etc/cron/weekly ]; then
	echo ... created /etc/cron/weekly folder >> ${log}
	cp -fr /etc/cron.weekly/* /etc/cron/weekly/
        rm -fr /etc/cron.weekly
        ln -fs /etc/cron/weekly /etc/cron.weekly
fi
install -m 0755 -o root -g root -d /etc/cron/monthly
if [ ! /etc/cron.monthly -ef /etc/cron/monthly ]; then
	echo ... created /etc/cron/monthly folder >> ${log}
	cp -fr /etc/cron.monthly/* /etc/cron/monthly/
        rm -fr /etc/cron.monthly
        ln -fs /etc/cron/monthly /etc/cron.monthly
fi

