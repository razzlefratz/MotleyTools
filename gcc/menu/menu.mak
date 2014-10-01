# file: menu/menu.mak

# ====================================================================
# files;
# --------------------------------------------------------------------

menu.o: menu.c cmassoc.h menu.h 
menudefine.o: menudefine.c tools.h memory.h menu.h types.h
menudump.o: menudump.c menu.h types.h
menulength.o: menulength.c menu.h types.h
menulist.o: menulist.c menu.h types.h
menuload.o: menuload.c menu.h types.h
menulookup.o: menulookup.c menu.h types.h
menuprefix.o: menuprefix.c menu.h types.h
menushow.o: menushow.c menu.h memory.h types.h
menusize.o: menusize.c menu.h types.h
menusort.o: menusort.c menu.h types.h
menuvolume.o: menuvolume.c menu.h types.h

