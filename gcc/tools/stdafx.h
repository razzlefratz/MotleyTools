/*====================================================================*
 *
 *   stdafx.h - do-nothing stub for microsoft c++ include file;
 *
 *   The microsoft c++ compiler required the includesion of <stdafx.h> for
 *   all c++ programs.
 *
 *--------------------------------------------------------------------*/

#define _O_RDONLY O_RDONLY
#define _O_RDRW   O_RDRW

#define _open(path, mode) open(path,mode)
#define  _read(fd, buffer, length)  read(fd, buffer, length)
#define _write(fd, buffer, length) write(fd, buffer, length)
#define _lseek(fd, offset, length) lseek(fd, offset, length)
#define _close(fd) close(fd)

#include <unistd.h>



