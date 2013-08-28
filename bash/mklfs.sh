# Published 2004 by Charles Maier Associates Limited for internal use;

# ====================================================================
#
# --------------------------------------------------------------------

export lfs=${PWD}/lfs
echo -n "enter lfs root [${lfs}] "
read answer
if [ ! -z ${answer} ]; then
	export lfs=${answer}
fi

# ====================================================================
# remove folders;
# --------------------------------------------------------------------

rm -fr ${lfs}/*

# ====================================================================
# create folders;
# --------------------------------------------------------------------

mkdir ${lfs}/bin
mkdir ${lfs}/boot
mkdir ${lfs}/dev 
mkdir ${lfs}/etc
mkdir ${lfs}/home
mkdir ${lfs}/lib
mkdir ${lfs}/mnt 
mkdir ${lfs}/root
mkdir ${lfs}/sbin
mkdir ${lfs}/tmp
mkdir ${lfs}/usr

mkdir ${lfs}/usr/bin
mkdir ${lfs}/usr/include
mkdir ${lfs}/usr/lib
mkdir ${lfs}/usr/local
mkdir ${lfs}/usr/local/bin
mkdir ${lfs}/usr/local/include
mkdir ${lfs}/usr/local/lib
mkdir ${lfs}/usr/local/sbin
mkdir ${lfs}/usr/local/share
mkdir ${lfs}/usr/local/share/man
mkdir ${lfs}/usr/local/share/man/man1
mkdir ${lfs}/usr/local/share/man/man2
mkdir ${lfs}/usr/local/share/man/man3
mkdir ${lfs}/usr/local/share/man/man4
mkdir ${lfs}/usr/local/share/man/man5
mkdir ${lfs}/usr/local/share/man/man6
mkdir ${lfs}/usr/local/share/man/man7
mkdir ${lfs}/usr/local/share/man/man8
mkdir ${lfs}/usr/local/share/man/man9
mkdir ${lfs}/usr/sbin
mkdir ${lfs}/usr/share
mkdir ${lfs}/usr/share/doc
mkdir ${lfs}/usr/share/man
mkdir ${lfs}/usr/share/man/man1
mkdir ${lfs}/usr/share/man/man2
mkdir ${lfs}/usr/share/man/man3
mkdir ${lfs}/usr/share/man/man4
mkdir ${lfs}/usr/share/man/man5
mkdir ${lfs}/usr/share/man/man6
mkdir ${lfs}/usr/share/man/man7
mkdir ${lfs}/usr/share/man/man8
mkdir ${lfs}/usr/share/man/man9
mkdir ${lfs}/usr/share/info
mkdir ${lfs}/usr/src
mkdir ${lfs}/opt
mkdir ${lfs}/var
mkdir ${lfs}/var/cache
mkdir ${lfs}/var/lock
mkdir ${lfs}/var/log
mkdir ${lfs}/var/run
mkdir ${lfs}/var/spool

# ====================================================================
# create symlinks;
# --------------------------------------------------------------------

ln -sf sbin ${lfs}/libexec
ln -sf sbin ${lfs}/usr/libexec
ln -sf sbin ${lfs}/usr/local/libexec
ln -sf usr/doc ${lfs}/doc 
ln -sf usr/man ${lfs}/man 
ln -sf usr/share ${lfs}/share
ln -sf share/doc ${lfs}/usr/doc
ln -sf share/man ${lfs}/usr/man
ln -sf share/info ${lfs}/usr/info
ln -sf share/doc ${lfs}/usr/local/doc   
ln -sf share/man ${lfs}/usr/local/man   
ln -sf share/info ${lfs}/usr/local/info  
ln -sf ../etc ${lfs}/usr/local/etc
ln -sf ../var ${lfs}/usr/local/var
ln -sf ../etc ${lfs}/usr/etc 
ln -sf ../var ${lfs}/usr/var

# ====================================================================
# finish 
# --------------------------------------------------------------------

echo done.

