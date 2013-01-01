
int main (int argc, char const * argv []) 

{
	char const* interface = "fxp0";
	ethernet_frame * frame;
	ifreq bound_if;
	charar buf [11] = 
	{
		0
	};
	int buf_len = 1;
	int bpf = 0;
	bpf_hdr * bpf_buf = new bpf_hdr [buf_len];
	bpf_hdr * bpf_packet;
	int i;
	for (i = 0; i < 99; i++) 
	{
		sprintf (buf, "/dev/bpf%i", i);
		if ((bpf = open (buf, O_RDWR)) != -1) 
		{
			break;
		}
	}
	strcpy (bound_if.ifr_name, interface);
	if (ioctl (bpf, BIOCSETIF, &bound_if) > 0) 
	{
		return (-1);
	}
	if (ioctl (bpf, BIOCIMMEDIATE, &buf_len) == -1) 
	{
		return (-1);
	}
	if (ioctl (bpf, BIOCGBLEN, &buf_len) == -1) 
	{
		return (-1);
	}
	read (bpf, bpf_buf, bpf_len);
	frame = (ethernet_frame*) ((byte *) (bpf_buf) + bpf_buf->bh_hdrlen);
	while (run_loop) 
	{
		memset (bpf_buf, 0, buf_len);
		if ((read_bytes = read (bpf, bpf_buf, buf_len)) > 0) 
		{
			char* ptr = reinterpret_cast<char*>(bpf_buf);
			while (ptr < (reinterpret_cast<char*>(bpf_buf) + read_bytes)) 
			{
				bpf_packet = reinterpret_cast<bpf_hdr*>(ptr);
				frame = (ethernet_frame*)((byte *) (bpf_packet) + bpf_packet->bh_hdrlen);
				ptr += BPF_WORDALIGN (bpf_packet->bh_hdrlen + bpf_packet->bh_caplen);
			}
		}
	}
	write (bpf, frame, bpf_buf->bh_caplen);
	return (0);
}

