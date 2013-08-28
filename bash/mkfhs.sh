#!/bin/bash
# file: mkfhs.sh
# Published 2004 by Charles Maier Associates Limited for internal use;

# ====================================================================
# create CMLinux FHS/LFS/LSB symlinks in / folder;
# --------------------------------------------------------------------

if [ ! /libexec -ef /sbin ]; then 
	if [ -d /libexec ]; then
		if [ -f /libexec/* ]; then
			echo move /libexec ...
			cp -fr /libexec/* /sbin
		fi
		rm -fr /libexec
	fi
	echo link /libexec ...
	ln -fs sbin /libexec
fi

if [ ! /share -ef /usr/share ]; then 
	if [ -d /share ]; then
		if [ -f /share/* ]; then
			echo move /share ...
			cp -fr /share/* /usr/share
		fi
		rm -fr /share
	fi
	echo link /share ...
	ln -fs usr/share /share
fi

if [ ! /man -ef /share/man ]; then
	if [ -d /man ]; then
		if [ -f /man/* ]; then
			echo move /man ...
			cp -fr /man/* /share/man
		fi
		rm -fr /man
	fi
	echo link /man ...
	ln -fs share/man /man
fi

if [ ! /doc -ef /share/doc ]; then
	if [ -d /doc ]; then
		if [ -f /doc/* ]; then
			echo move /doc ...
			cp -fr /doc/* /share/doc
		fi
		rm -fr /doc
	fi
	echo link /doc ...
	ln -fs share/doc /doc
fi

if [ ! /info -ef /share/info ]; then
	if [ -d /info ]; then
			echo move /info ...
			cp -fr /info/* /share/info
		rm -fr /info
	fi
	echo link /info ...
	ln -fs share/info /info
fi

# ====================================================================
# create CMLinux FHS/LFS/LSB symlinks in /usr folder;
# --------------------------------------------------------------------

if [ ! /usr/etc -ef /etc ]; then 
	if [ -d /usr/etc ]; then 
		if [ -d /usr/etc/* ]; then 
			echo move /usr/etc ...
			cp -fr /usr/etc/* /etc
		fi
		rm -fr /usr/etc
	fi
	echo link /usr/etc ...
	ln -fs ../etc /usr/etc
fi

if [ ! /usr/libexec -ef /usr/sbin ]; then 
	if [ -d /usr/libexec ]; then
		if [ -f /usr/libexec/* ]; then
			echo move /usr/libexec ...
			cp -fr /usr/libexec/* /usr/sbin
		fi
		rm -fr /usr/libexec
	fi
	echo link /usr/libexec ...
	ln -fs sbin /usr/libexec
fi

if [ ! /usr/man -ef /usr/share/man ]; then 
	if [ -d /usr/man ]; then
		if [ -d /usr/man/* ]; then
			echo move /usr/man ...
			cp -fr /usr/man/* /usr/share/man
		fi
		rm -fr /usr/man
	fi
	echo move /usr/man ...
	ln -fs share/man /usr/man
fi

if [ ! /usr/doc -ef /usr/share/doc ]; then 
	if [ -d /usr/doc ]; then
		if [ -d /usr/doc/* ]; then
			echo move /usr/doc ...
			cp -fr /usr/doc/* /usr/share/doc
		fi
		rm -fr /usr/doc
	fi
	echo link /usr/doc ...
	ln -fs share/doc /usr/doc
fi

if [ ! /usr/info -ef /usr/share/info ]; then 
	if [ -d /usr/info ]; then
		if [ -d /usr/info/* ]; then
			echo move /usr/info ...
			cp -fr /usr/info/* /usr/share/info
		fi
		rm -fr /usr/info
	fi
	echo link /usr/info ...
	ln -fs share/info /usr/info
fi

if [ ! /usr/var -ef /var ]; then 
	if [ -d /usr/var ]; then 
		if [ -d /usr/var/* ]; then 
			echo move /usr/var ...
			cp -fr /usr/var/* /var
		fi
		rm -fr /usr/var
	fi
	echo link /usr/var ...
	ln -fs ../var /usr/var
fi

# ====================================================================
# create CMLinux FHS/LFS/LSB symlinks in /var folder;
# --------------------------------------------------------------------

if [ ! /var/lib -ef /var/state ]; then 
	echo make /var/state ...
	install -m 0755 -o root -g root -d /var/state
	if [ -d /usr/lib ]; then 
		if [ -d /var/lib/* ]; then 
			echo move /var/lib to /var/state ...
			cp -fr /var/lib/* /var/state
		fi
		rm -fr /var/lib
	fi
	echo link /var/lib ...
	ln -fs state /var/lib
fi

# ====================================================================
# create CMLinux FHS/LFS/LSB symlinks in /usr/local folder;
# --------------------------------------------------------------------

if [ ! /usr/local/etc -ef /usr/etc ]; then 
	if [ -d /usr/local/etc ]; then 
		if [ -d /usr/local/etc/* ]; then 
			echo move /usr/local/etc ...
			cp -fr /usr/local/etc/* /etc
		fi
		rm -fr /usr/local/etc
	fi
	echo link /usr/local/etc ...
	ln -fs ../etc /usr/local/etc
fi

if [ ! /usr/local/libexec -ef /usr/local/sbin ]; then 
	if [ -d /usr/local/libexec ]; then
		if [ -d /usr/local/libexec/* ]; then
			echo move /usr/local/libexec ...
			cp -fr /usr/local/libexec/* /usr/local/sbin
		fi
		rm -fr /usr/local/libexec
	fi
	echo link /usr/local/libexec ...
	ln -fs sbin /usr/local/libexec
fi

if [ ! /usr/local/man -ef /usr/local/share/man ]; then
	if [ -d /usr/local/man ]; then
		if [ -d /usr/local/man/* ]; then
			echo move /usr/local/man ...
			cp -fr /usr/local/man/* /usr/local/share/man
		fi
		rm -fr /usr/local/man     
	fi
	echo link /usr/local/man ...
	ln -sf share/man /usr/local/man
fi

if [ ! /usr/local/doc -ef /usr/local/share/doc ]; then
	if [ -d /usr/local/doc ]; then
		if [ -d /usr/local/doc/* ]; then
			echo move /usr/local/doc ...
			cp -fr /usr/local/doc/* /usr/local/share/doc
		fi
		rm -fr /usr/local/doc
	fi
	echo link /usr/local/doc ...
	ln -sf share/doc /usr/local/doc
fi

if [ ! /usr/local/info -ef /usr/local/share/info ]; then
	if [ -d /usr/local/info ]; then
		if [ -d /usr/local/info/* ]; then
			echo move /usr/local/info ...
			cp -fr /usr/local/info/* /usr/local/share/info
		fi
		rm -fr /usr/local/info
	fi
	echo link /usr/local/info ...
	ln -sf share/info /usr/local/info
fi

if [ ! /usr/local/var -ef /usr/var ]; then 
	if [ -d /usr/local/var ]; then 
		if [ -d /usr/local/var/* ]; then 
			echo move /usr/local/var ...
			cp -fr /usr/local/var/* /var
		fi
		rm -fr /usr/local/var
	fi
	echo link /usr/local/var ...
	ln -fs ../var /usr/local/var
fi

# ====================================================================
# create FHS compliant /usr/share folders 
# --------------------------------------------------------------------

install -m 2755 -o root -g root -d /usr/share/man
install -m 2755 -o root -g root -d /usr/share/doc
install -m 2755 -o root -g root -d /usr/share/info
install -m 2755 -o root -g root -d /usr/share/man/man1
install -m 2755 -o root -g root -d /usr/share/man/man2
install -m 2755 -o root -g root -d /usr/share/man/man3
install -m 2755 -o root -g root -d /usr/share/man/man4
install -m 2755 -o root -g root -d /usr/share/man/man5
install -m 2755 -o root -g root -d /usr/share/man/man6
install -m 2755 -o root -g root -d /usr/share/man/man7
install -m 2755 -o root -g root -d /usr/share/man/man8
install -m 2755 -o root -g root -d /usr/share/man/man9
install -m 2755 -o root -g root -d /usr/local/share/man
install -m 2755 -o root -g root -d /usr/local/share/doc
install -m 2755 -o root -g root -d /usr/local/share/info
install -m 2755 -o root -g root -d /usr/local/share/man/man1
install -m 2755 -o root -g root -d /usr/local/share/man/man2
install -m 2755 -o root -g root -d /usr/local/share/man/man3
install -m 2755 -o root -g root -d /usr/local/share/man/man4
install -m 2755 -o root -g root -d /usr/local/share/man/man5
install -m 2755 -o root -g root -d /usr/local/share/man/man6
install -m 2755 -o root -g root -d /usr/local/share/man/man7
install -m 2755 -o root -g root -d /usr/local/share/man/man8
install -m 2755 -o root -g root -d /usr/local/share/man/man9

# ====================================================================
# create FHS compliant /var folders 
# --------------------------------------------------------------------

install -m 2755 -o root -g root -d /var/cache
install -m 2755 -o root -g root -d /var/lib
install -m 2755 -o root -g root -d /var/lib/misc
install -m 2755 -o root -g root -d /var/log
install -m 2755 -o root -g root -d /var/spool
install -m 2755 -o root -g root -d /var/run

install -m 2755 -o root -g root -d /usr/X11R6
install -m 2755 -o root -g root -d /usr/X11R6/bin
Install -m 2755 -o root -g root -d /usr/X11R6/lib/X11
install -m 2755 -o root -g root -d /usr/X11R6/include/X11

# restore FHS compliant symlinks 
ln -fs ../X11R6/bin /usr/bin/X11
ln -fs ../X11R6/lib/X11 /usr/lib/X11
ln -fs ../X11R6/include/X11 /usr/include/X11
ln -fs ../etc/X11 /usr/X11R6/etc 

# ====================================================================
# 
# --------------------------------------------------------------------

echo done.

