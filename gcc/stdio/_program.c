
static char const *usage [] = 

{
	"progam",
	"h",
	PUTOPT_S_FUNNEL,
	"another wonderful program from charles maier associates",
	"h\thelp summary ",
	NULL
};

signed c;
optind = 1;
opterr = 1;
while ((c = getopt (argc, argv, usage [PUTOPT_I_OPTIONS])) != -1) 

{
	switch (c) 
	{
	case 'h':
		putopt (usage, 0);
	default:
		exit (1);
	}
}

}
