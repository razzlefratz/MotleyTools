/*====================================================================*
 *
 *   void set_fl (int fd, int flags);
 *
 *
 *
 *--------------------------------------------------------------------*/

void set_fl (signed fd, signed flags) 

{
	signed value;
	if ((value = fcntl (fd, F_GETFL, 0)) < 0) 
	{
		eperror ("fcntl F_GETFL failed.");
		exit (1);
	}
	value |= flags;
	if (fcntl (fd, F_SETFL, value) < 0) 
	{
		eperror ("fcntl F_SETFL failed.");
		exit (1);
	}
	return;
}

