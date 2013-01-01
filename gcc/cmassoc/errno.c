/*====================================================================*
 *
 *   errno.c - print system error message text on stdout 
 *
 *   this program is a simple debugging tool that displays the argument
 *   vector argv[] on stdout for inspection.
 *
 *   use it to see how your host system processes command line arguments;
 *
 *   000 Unknown error: 0
 *   001 Operation not permitted
 *   002 No such file or directory
 *   003 No such process
 *   004 Interrupted system call
 *   005 Input/output error
 *   006 Device not configured
 *   007 Argument list too long
 *   008 Exec format error
 *   009 Bad file descriptor
 *   010 No child processes
 *   011 Resource deadlock avoided
 *   012 Cannot allocate memory
 *   013 Permission denied
 *   014 Bad address
 *   015 Block device required
 *   016 Resource busy
 *   017 File exists
 *   018 Cross-device link
 *   019 Operation not supported by device
 *   020 Not a directory
 *   021 Is a directory
 *   022 Invalid argument
 *   023 Too many open files in system
 *   024 Too many open files
 *   025 Inappropriate ioctl for device
 *   026 Text file busy
 *   027 File too large
 *   028 No space left on device
 *   029 Illegal seek
 *   030 Read-only file system
 *   031 Too many links
 *   032 Broken pipe
 *   033 Numerical argument out of domain
 *   034 Result too large
 *   035 Resource temporarily unavailable
 *   036 Operation now in progress
 *   037 Operation already in progress
 *   038 Socket operation on non-socket
 *   039 Destination address required
 *   040 Message too long
 *   041 Protocol wrong type for socket
 *   042 Protocol not available
 *   043 Protocol not supported
 *   044 Socket type not supported
 *   045 Operation not supported
 *   046 Protocol family not supported
 *   047 Address family not supported by protocol family
 *   048 Address already in use
 *   049 Can't assign requested address
 *   050 Network is down
 *   051 Network is unreachable
 *   052 Network dropped connection on reset
 *   053 Software caused connection abort
 *   054 Connection reset by peer
 *   055 No buffer space available
 *   056 Socket is already connected
 *   057 Socket is not connected
 *   058 Can't send after socket shutdown
 *   059 Too many references: can't splice
 *   060 Operation timed out
 *   061 Connection refused
 *   062 Too many levels of symbolic links
 *   063 File name too long
 *   064 Host is down
 *   065 No route to host
 *   066 Directory not empty
 *   067 Too many processes
 *   068 Too many users
 *   069 Disc quota exceeded
 *   070 Stale NFS file handle
 *   071 Too many levels of remote in path
 *   072 RPC struct is bad
 *   073 RPC version wrong
 *   074 RPC prog. not avail
 *   075 Program version wrong
 *   076 Bad procedure for program
 *   077 No locks available
 *   078 Function not implemented
 *   079 Inappropriate file type or format
 *   080 Authentication error
 *   081 Need authenticator
 *   082 Device power is off
 *   083 Device error
 *   084 Value too large to be stored in data type
 *   085 Bad executable (or shared library)
 *   086 Bad CPU type in executable
 *   087 Shared library version mismatch
 *   088 Malformed Mach-o file
 *   089 Operation canceled
 *   090 Identifier removed
 *   091 No message of desired type
 *   092 Illegal byte sequence
 *   093 Attribute not found
 *   094 Bad message
 *   095 EMULTIHOP (Reserved)
 *   096 No message available on STREAM
 *   097 ENOLINK (Reserved)
 *   098 No STREAM resources
 *   099 Not a STREAM
 *   100 Protocol error
 *   101 STREAM ioctl timeout
 *   102 Operation not supported on socket
 *   103 Policy not found
 *
 *.  Motley Tools by Charles Maier
 *:  Published 1982-2005 by Charles Maier for personal use
 *;  Licensed under the Internet Software Consortium License
 *
 *--------------------------------------------------------------------*/

#include <stdio.h>
#include <string.h>

int main (int argc, char const * argv []) 

{
	int error;
	for (error = 0; error < 255; error++) 
	{
		printf ("%03d %s\n", error, strerror (error));
	}
	return (0);
}

