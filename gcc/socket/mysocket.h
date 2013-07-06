
static struct socket unixsock = 

{
	&unixsock,
	&unixsock,
	(file_t) (-1),
	(size_t) (sizeof (unixsock_addr)),
	(struct sockaddr *)(&unixsock_addr),
	(char *)(0)
};

