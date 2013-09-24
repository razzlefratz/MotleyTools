/*====================================================================*
 *
 *   unistd.h - do-nothing stub for microsoft c++ include file;
 *
 *.  Motley Tools by Charles Maier
 *:  modified sun 07 sep 03 by user root on host zeus;
 *;  Licensed under the Internet Software Consortium License
 *
 *--------------------------------------------------------------------*/

#define _O_RDONLY O_RDONLY
#define _O_RDRW   O_RDRW

#define _open(path, mode) open(path,mode)
#define  _read(fd, buffer, length)  read(fd, buffer, length)
#define _write(fd, buffer, length) write(fd, buffer, length)
#define _lseek(fd, offset, length) lseek(fd, offset, length)
#define _close(fd) close(fd)

size_t read(int, void *, size_t);
size_t write(int, void const *, size_t);
int close(int);

#define STDIN_FILENO  0
#define STDOUT_FILENO 1
#define STDERR_FILENO 2



