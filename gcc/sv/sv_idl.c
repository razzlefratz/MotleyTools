/*====================================================================*
 *
 *   sv_idl[] -
 *
 *.  Motley Tools by Charles Maier
 *:  Published 1982-2005 by Charles Maier for personal use
 *;  Licensed under the Internet Software Consortium License
 *
 *--------------------------------------------------------------------*/

#include <stddef.h>

/*====================================================================*
 *   program constants;
 *--------------------------------------------------------------------*/

#define IDL_O_BOOLEAN                     0
#define IDL_O___INT3264                   1
#define IDL_O___INT64                     2
#define IDL_O_AGGREGATABLE                3
#define IDL_O_ALLOCATE                    4
#define IDL_O_APPOBJECT                   5
#define IDL_O_ARRAYS                      6
#define IDL_O_ASYNC                       7
#define IDL_O_ASYNC_UUID                  8
#define IDL_O_AUTO_HANDLE                 9
#define IDL_O_BINDABLE                   10
#define IDL_O_BROADCAST                  11
#define IDL_O_BYTE                       12
#define IDL_O_BYTE_COUNT                 13
#define IDL_O_CALL_AS                    14
#define IDL_O_CALLBACK                   15
#define IDL_O_CHAR                       16
#define IDL_O_COCLASS                    17
#define IDL_O_CODE                       18
#define IDL_O_COMM_STATUS                19
#define IDL_O_CONST                      20
#define IDL_O_CONTEXT_HANDLE             21
#define IDL_O_CONTEXT_HANDLE_NOSERIALIZE  22
#define IDL_O_CONTEXT_HANDLE_SERIALIZE   23
#define IDL_O_CONTROL                    24
#define IDL_O_CPP_QUOTE                  25
#define IDL_O_CUSTOM                     26
#define IDL_O_DECODE                     27
#define IDL_O_DEFAULT                    28
#define IDL_O_DEFAULTBIND                29
#define IDL_O_DEFAULTCOLLELEM            30
#define IDL_O_DEFAULTVALUE               31
#define IDL_O_DEFAULTVTABLE              32
#define IDL_O_DISPINTERFACE              33
#define IDL_O_DISPLAYBIND                34
#define IDL_O_DLLNAMESTR                 35
#define IDL_O_DOUBLE                     36
#define IDL_O_DUAL                       37
#define IDL_O_ENABLE_ALLOCATE            38
#define IDL_O_ENCODE                     39
#define IDL_O_ENDPOINT                   40
#define IDL_O_ENTRY                      41
#define IDL_O_ENUM                       42
#define IDL_O_ERROR_STATUS_T             43
#define IDL_O_EXPLICIT_HANDLE            44
#define IDL_O_FAULT_STATUS               45
#define IDL_O_FIRST_IS                   46
#define IDL_O_FLOAT                      47
#define IDL_O_FORCE_ALLOCATE             48
#define IDL_O_HANDLE                     49
#define IDL_O_HANDLE_T                   50
#define IDL_O_HEAP                       51
#define IDL_O_HELPCONTEXT                52
#define IDL_O_HELPFILE                   53
#define IDL_O_HELPSTRING                 54
#define IDL_O_HELPSTRINGCONTEXT          55
#define IDL_O_HELPSTRINGDLL              56
#define IDL_O_HIDDEN                     57
#define IDL_O_HYPER                      58
#define IDL_O_ID                         59
#define IDL_O_IDEMPOTENT                 60
#define IDL_O_IGNORE                     61
#define IDL_O_IID_IS                     62
#define IDL_O_IMMEDIATEBIND              63
#define IDL_O_IMPLICIT_HANDLE            64
#define IDL_O_IMPORT                     65
#define IDL_O_IMPORTLIB                  66
#define IDL_O_IN                         67
#define IDL_O_IN_LINE                    68
#define IDL_O_INCLUDE                    69
#define IDL_O_INT                        70
#define IDL_O_INTERFACE                  71
#define IDL_O_LAST_ISE                   72
#define IDL_O_LCID                       73
#define IDL_O_LENGTH_IS                  74
#define IDL_O_LIBRARY                    75
#define IDL_O_LICENSED                   76
#define IDL_O_LOCAL                      77
#define IDL_O_LONG                       78
#define IDL_O_MAX_IS                     79
#define IDL_O_MAYBE                      80
#define IDL_O_MESSAGE                    81
#define IDL_O_MIDL_PRAGMAWARNING         82
#define IDL_O_MIDL_USER_ALLOCATE         83
#define IDL_O_MIDL_USER_FREE             84
#define IDL_O_MIN_IS                     85
#define IDL_O_MODULE                     86
#define IDL_O_MS_UNION                   87
#define IDL_O_NCACN_AT_DSP               88
#define IDL_O_NCACN_DNET_NSP             89
#define IDL_O_NCACN_HTTP                 90
#define IDL_O_NCACN_IP_TCP               91
#define IDL_O_NCACN_NB_IPX               92
#define IDL_O_NCACN_NB_NB                93
#define IDL_O_NCACN_NB_TCP               94
#define IDL_O_NCACN_NP                   95
#define IDL_O_NCACN_SPX                  96
#define IDL_O_NCACN_VNS_SPP              97
#define IDL_O_NCADG_IP_UDP               98
#define IDL_O_NCADG_IPX                  99
#define IDL_O_NCADG_MQ                  100
#define IDL_O_NCALRPC                   101
#define IDL_O_NOCODE                    102
#define IDL_O_NONBROWSABLE              103
#define IDL_O_NONCREATABLE              104
#define IDL_O_NONEXTENSIBLE             105
#define IDL_O_NOTIFY                    106
#define IDL_O_NOTIFY_FLAG               107
#define IDL_O_OBJECT                    108
#define IDL_O_ODL                       109
#define IDL_O_OLEAUTOMATION             110
#define IDL_O_OPTIMIZE                  111
#define IDL_O_OPTIONAL                  112
#define IDL_O_OUT                       113
#define IDL_O_OUT_OF_LINE               114
#define IDL_O_PARTIAL_IGNORE            115
#define IDL_O_PIPE                      116
#define IDL_O_POINTER_DEFAULT           117
#define IDL_O_PRAGMA                    118
#define IDL_O_PROPGET                   119
#define IDL_O_PROPPUT                   120
#define IDL_O_PROPPUTREF                121
#define IDL_O_PROXY                     122
#define IDL_O_PTR                       123
#define IDL_O_PUBLIC                    124
#define IDL_O_RANGE                     125
#define IDL_O_READONLY                  126
#define IDL_O_REF                       127
#define IDL_O_REPRESENT_AS              128
#define IDL_O_REQUESTEDIT               129
#define IDL_O_RESTRICTED                130
#define IDL_O_RETVAL                    131
#define IDL_O_SHAPE                     132
#define IDL_O_SHORT                     133
#define IDL_O_SIGNED                    134
#define IDL_O_SIZE_IS                   135
#define IDL_O_SMALL                     136
#define IDL_O_SOURCE                    137
#define IDL_O_STRICT_CONTEXT_HANDLE     138
#define IDL_O_STRING                    139
#define IDL_O_STRUCT                    140
#define IDL_O_SWITCH                    141
#define IDL_O_SWITCH_IS                 142
#define IDL_O_SWITCH_TYPE               143
#define IDL_O_TRANSMIT_AS               144
#define IDL_O_TYPEDEF                   145
#define IDL_O_UIDEFAULT                 146
#define IDL_O_UNION                     147
#define IDL_O_UNIQUE                    148
#define IDL_O_UNSIGNED                  149
#define IDL_O_USER_MARSHAL              150
#define IDL_O_USESGETLASTERROR          151
#define IDL_O_UUID                      152
#define IDL_O_V1_ENUM                   153
#define IDL_O_VARARG                    154
#define IDL_O_VERSION                   155
#define IDL_O_VOID                      156
#define IDL_O_WCHAR_T                   157
#define IDL_O_WIRE_MARSHAL              158
#define IDL_O_NULL                      159

/*====================================================================*
 *   program variables;
 *--------------------------------------------------------------------*/

char const *sv_idl [] = 

{
	"boolean",
	"__int3264",
	"__int64",
	"aggregatable",
	"allocate",
	"appobject",
	"arrays",
	"async",
	"async_uuid",
	"auto_handle",
	"bindable",
	"broadcast",
	"byte",
	"byte_count",
	"call_as",
	"callback",
	"char",
	"coclass",
	"code",
	"comm_status",
	"const",
	"context_handle",
	"context_handle_noserialize",
	"context_handle_serialize",
	"control",
	"cpp_quote",
	"custom",
	"decode",
	"default",
	"defaultbind",
	"defaultcollelem",
	"defaultvalue",
	"defaultvtable",
	"dispinterface",
	"displaybind",
	"dllname(str)",
	"double",
	"dual",
	"enable_allocate",
	"encode",
	"endpoint",
	"entry",
	"enum",
	"error_status_t",
	"explicit_handle",
	"fault_status",
	"first_is",
	"float",
	"force_allocate",
	"handle",
	"handle_t",
	"heap",
	"helpcontext",
	"helpfile",
	"helpstring",
	"helpstringcontext",
	"helpstringdll",
	"hidden",
	"hyper",
	"id",
	"idempotent",
	"ignore",
	"iid_is",
	"immediatebind",
	"implicit_handle",
	"import",
	"importlib",
	"in",
	"in_line",
	"include",
	"int",
	"interface",
	"last_ise",
	"lcid",
	"length_is",
	"library",
	"licensed",
	"local",
	"long",
	"max_is",
	"maybe",
	"message",
	"midl_pragma warning",
	"midl_user_allocate",
	"midl_user_free",
	"min_is",
	"module",
	"ms_union",
	"ncacn_at_dsp",
	"ncacn_dnet_nsp",
	"ncacn_http",
	"ncacn_ip_tcp",
	"ncacn_nb_ipx",
	"ncacn_nb_nb",
	"ncacn_nb_tcp",
	"ncacn_np",
	"ncacn_spx",
	"ncacn_vns_spp",
	"ncadg_ip_udp",
	"ncadg_ipx",
	"ncadg_mq",
	"ncalrpc",
	"nocode",
	"nonbrowsable",
	"noncreatable",
	"nonextensible",
	"notify",
	"notify_flag",
	"object",
	"odl",
	"oleautomation",
	"optimize",
	"optional",
	"out",
	"out_of_line",
	"partial_ignore",
	"pipe",
	"pointer_default",
	"pragma",
	"propget",
	"propput",
	"propputref",
	"proxy",
	"ptr",
	"public",
	"range",
	"readonly",
	"ref",
	"represent_as",
	"requestedit",
	"restricted",
	"retval",
	"shape",
	"short",
	"signed",
	"size_is",
	"small",
	"source",
	"strict_context_handle",
	"string",
	"struct",
	"switch",
	"switch_is",
	"switch_type",
	"transmit_as",
	"typedef",
	"uidefault",
	"union",
	"unique",
	"unsigned",
	"user_marshal",
	"usesgetlasterror",
	"uuid",
	"v1_enum",
	"vararg",
	"version",
	"void",
	"wchar_t",
	"wire_marshal",
	NULL
};

