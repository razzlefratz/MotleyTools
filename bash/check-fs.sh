#!/bin/bash
# file: /usr/local/bin/cmassoc/checkroot.sh
# Published 2005 by Charles Maier Associates Limited for internal use;

# ====================================================================
# confirm that non-standard root folders do not exist;
# --------------------------------------------------------------------

echo "checking CMLinux root folders ..."
for file in /*; do 
	if [ -d ${file} ]; then
		name=$(basename ${file})
		case ${name} in 
			cdrom|floppy|disk[0-9]) ;; 
			bin|boot|dev|doc|etc|home|include|info|initrd|lfs|lib|libexec|lost+found|man|mnt|opt|proc|root|sbin|share|tmp|usr|var) ;; 
			*) echo "... ${file} should not exist." ;;
		esac
	else
		echo "... ${file} is stray."
	fi
done

# ====================================================================
# confirm that non-standard /var folders do not exist;
# --------------------------------------------------------------------

echo "checking CMLinux var folders ..."
for file in /var/*; do 
	if [ -d ${file} ]; then
		name=$(basename ${file})
		case ${name} in 
			backups|cache|lib|local|lock|log|lost+found|mail|opt|run|spool|state|tmp) ;; 
			*) echo "... ${file} should not exist." ;;
		esac
	else
		echo "... ${file} is stray."
	fi
done

# ====================================================================
# look for regular files in folders that should be empty;
# --------------------------------------------------------------------

echo "checking CMLinux for stray files ..."
for folder in /{.,usr/{.,local,opt,share,var},opt,share,var}; do
	for file in ${folder}/*; do
		if [ -f ${file} ]; then
			echo "... ${file} is stray."
		fi
	done
done

# ====================================================================
#
# --------------------------------------------------------------------

exit 0

