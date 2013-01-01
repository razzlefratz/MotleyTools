/*====================================================================*
 *
 *   sv_shirename -
 *
 *.  Motley Tools by Charles Maier
 *:  Published 1982-2005 by Charles Maier for personal use
 *;  Licensed under the Internet Software Consortium License
 *
 *--------------------------------------------------------------------*/

#include <stddef.h>

#define SHIRENAME_O_AVON                      0
#define SHIRENAME_O_BEDFORDSHIRE              1
#define SHIRENAME_O_BERKSHIRE                 2
#define SHIRENAME_O_BORDERS                   3
#define SHIRENAME_O_BUCKINGHAMSHIRE           4
#define SHIRENAME_O_CAMBRIDGESHIRE            5
#define SHIRENAME_O_CENTRAL                   6
#define SHIRENAME_O_CHESHIRE                  7
#define SHIRENAME_O_CLEVELAND                 8
#define SHIRENAME_O_CLWYD                     9
#define SHIRENAME_O_CORNWALL                 10
#define SHIRENAME_O_CUMBRIA                  11
#define SHIRENAME_O_DERBYSHIRE               12
#define SHIRENAME_O_DEVON                    13
#define SHIRENAME_O_DORSET                   14
#define SHIRENAME_O_DUMFRIES_GALLOWAY        15
#define SHIRENAME_O_DURHAM                   16
#define SHIRENAME_O_DYFED                    17
#define SHIRENAME_O_EAST_SUSSEX              18
#define SHIRENAME_O_ESSEX                    19
#define SHIRENAME_O_FIFE                     20
#define SHIRENAME_O_GLOUCESTERSHIRE          21
#define SHIRENAME_O_GRAMPIAN                 22
#define SHIRENAME_O_GREATER_LONDON           23
#define SHIRENAME_O_GREATER_MANCHESTER       24
#define SHIRENAME_O_GWENT                    25
#define SHIRENAME_O_GWYNEDD                  26
#define SHIRENAME_O_HAMPSHIRE                27
#define SHIRENAME_O_HEREFORD_WORCESTER       28
#define SHIRENAME_O_HERTFORDSHIRE            29
#define SHIRENAME_O_HIGHLAND                 30
#define SHIRENAME_O_HORTHUMBRIA              31
#define SHIRENAME_O_HUMBERSIDE               32
#define SHIRENAME_O_ISLE_OF_MAN              33
#define SHIRENAME_O_ISLE_OF_WIGHT            34
#define SHIRENAME_O_ISLES_OF_SCILLY          35
#define SHIRENAME_O_KENT                     36
#define SHIRENAME_O_LANCASHIRE               37
#define SHIRENAME_O_LEICESTER                38
#define SHIRENAME_O_LINCOLNSHIRE             39
#define SHIRENAME_O_LOTHIAN                  40
#define SHIRENAME_O_MERSEYSIDE               41
#define SHIRENAME_O_MID_GLAMORGAN            42
#define SHIRENAME_O_NORFOLK                  43
#define SHIRENAME_O_NORTH_YORKSHIRE          44
#define SHIRENAME_O_NORTHAMPTONSHIRE         45
#define SHIRENAME_O_NOTTINGHAMSHIRE          46
#define SHIRENAME_O_ORKNEY                   47
#define SHIRENAME_O_OXFORDSHIRE              48
#define SHIRENAME_O_POWYS                    49
#define SHIRENAME_O_SHETLAND                 50
#define SHIRENAME_O_SHROPSHIRE               51
#define SHIRENAME_O_SOMERSET                 52
#define SHIRENAME_O_SOUTH_GLAMORGAN          53
#define SHIRENAME_O_SOUTH_YORKSHIRE          54
#define SHIRENAME_O_STAFFORDSHIRE            55
#define SHIRENAME_O_STRATHCLYDE              56
#define SHIRENAME_O_SUFFOLK                  57
#define SHIRENAME_O_SURREY                   58
#define SHIRENAME_O_TAYSIDE                  59
#define SHIRENAME_O_TYNE_WEAR                60
#define SHIRENAME_O_WARWICKSHIRE             61
#define SHIRENAME_O_WEST_GLAMORGAN           62
#define SHIRENAME_O_WEST_MIDLANDS            63
#define SHIRENAME_O_WEST_SUSSEX              64
#define SHIRENAME_O_WEST_YORKSHIRE           65
#define SHIRENAME_O_WESTERN_ISLES            66
#define SHIRENAME_O_WILTSHIRE                67

#define SV_SHIRENAME  68

char *sv_shirename [SV_SHIRENAME+1] = 

{
	"Avon                   ",
	"Bedfordshire           ",
	"Berkshire              ",
	"Borders                ",
	"Buckinghamshire        ",
	"Cambridgeshire         ",
	"Central                ",
	"Cheshire               ",
	"Cleveland              ",
	"Clwyd                  ",
	"Cornwall               ",
	"Cumbria                ",
	"Derbyshire             ",
	"Devon                  ",
	"Dorset                 ",
	"Dumfries & Galloway    ",
	"Durham                 ",
	"Dyfed                  ",
	"East Susses            ",
	"Essex                  ",
	"Fife                   ",
	"Gloucestershire        ",
	"Grampian               ",
	"Greater London         ",
	"Greater Manchester     ",
	"Gwent                  ",
	"Gwynedd                ",
	"Hampshire              ",
	"Hereford & Worcester   ",
	"Hertfordshire          ",
	"Highland               ",
	"Horthumbria            ",
	"Humberside             ",
	"Isle of Man            ",
	"Isle of Wight          ",
	"Isles of Scilly        ",
	"Kent                   ",
	"Lancashire             ",
	"leicester              ",
	"Lincolnshire           ",
	"Lothian                ",
	"Merseyside             ",
	"Mid Glamorgan          ",
	"Norfolk                ",
	"North Yorkshire        ",
	"Northamptonshire       ",
	"Nottinghamshire        ",
	"Orkney                 ",
	"Oxfordshire            ",
	"Powys                  ",
	"Shetland               ",
	"Shropshire             ",
	"Somerset               ",
	"South Glamorgan        ",
	"South Yorkshire        ",
	"Staffordshire          ",
	"Strathclyde            ",
	"Suffolk                ",
	"Surrey                 ",
	"Tayside                ",
	"Tyne & Wear            ",
	"Warwickshire           ",
	"West Glamorgan         ",
	"West Midlands          ",
	"West Sussex            ",
	"West Yorkshire         ",
	"Western Isles          ",
	"Wiltshire              ",
	NULL
};

