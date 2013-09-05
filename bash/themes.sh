# ====================================================================
#
# --------------------------------------------------------------------

COMMAND=/home/gnome
{tbd}=/home/gnome
{src}=/home/gnome/themes
{log}=/home/gnome/themes.log

# ====================================================================
#
# --------------------------------------------------------------------

cd /usr/gnome/share/themes 

# ====================================================================
#
# --------------------------------------------------------------------

tar -vzxf ${src}/cmassoc-themes.tar.gz

# ====================================================================
#
# --------------------------------------------------------------------

# tar -vzxf ${src}/mcity/MCity-Carved-1.0.tar.gz 
# tar -vzxf ${src}/mcity/MCity-H2Oridium. ar.gz 
# tar -vzxf ${src}/mcity/MCity-Hacked.tar.gz
# tar -vzxf ${src}/mcity/MCity-Maggra-X.tar.gz
# tar -vzxf ${src}/mcity/MCity-MetaXP.tar.gz
# tar -vzxf ${src}/mcity/MCity-Metativo.tar.gz
# tar -vjxf ${src}/mcity/MCity-Milk-2.0.tar.tar
# tar -vzxf ${src}/mcity/MCity-Prion.tar.gz
# tar -vzxf ${src}/mcity/MCity-SmootS.tar.gz
# tar -vzxf ${src}/mcity/MCity-TigertCrack-1.2.1.tar.gz
# tar -vzxf ${src}/mcity/MCity-mwm-north.tar.gz

# ====================================================================
#
# --------------------------------------------------------------------

# tar -vjxf ${src}/gtk2/GTK2-Milk-2.0.tar.tar
# tar -vjxf ${src}/gtk2/GTK2-Titanium.tar.tar
# tar -vzxf ${src}/gtk2/GTK2-Prion.tar.gz
# tar -vzxf ${src}/gtk2/GTK2-XFCE-Engine-2.0.8.tar.gz

# ====================================================================
#
# --------------------------------------------------------------------

echo $(date) done >> ${log}
echo done

