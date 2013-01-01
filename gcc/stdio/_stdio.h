/*====================================================================*
 *
 *   _stdio.h - standard I/O declarations, definitions and prototypes;
 *
 *.  Motley Tools by Charles Maier
 *:  modified sun 07 sep 03 by user root on host zeus;
 *;  Licensed under the Internet Software Consortium License
 *
 *--------------------------------------------------------------------*/

#ifndef _STDIO_HEADER
#define _STDIO_HEADER

/*====================================================================*
 *
 *--------------------------------------------------------------------*/

#include "../stdlib/_stddef.h"
#include "../stdlib/_stdarg.h"

/*====================================================================*
 * define POSIX standard constants;
 *--------------------------------------------------------------------*/

#define FOPEN_MAX     20
#define FILENAME_MAX  260

/*====================================================================*
 * define physical/logical host system parameters;
 *--------------------------------------------------------------------*/

#define _MEMPAGE 512 /* size of physical memory page (bytes)  */
#define _BUFSIZE 512 /* size of physical I/O block (bytes) */

/*====================================================================*
 * define ANSI Standard constants;
 *--------------------------------------------------------------------*/

#ifndef BUFSIZ
#define BUFSIZ _BUFSIZE
#endif

#ifndef OPEN_MAX
#define OPEN_MAX FOPEN_MAX
#endif

#ifndef NULL
#define NULL ((void *)(0))
#endif

#ifndef NUL
#define NUL ((char)(0))
#endif

#ifndef EOF
#define EOF ((int)(-1))
#endif

#ifndef ERR
#define ERR ((int)(-1))
#endif

/*====================================================================*
 * define file control block flagword mask values;
 *--------------------------------------------------------------------*/

#define  STDIN 0 /* file descriptor for standard input */
#define STDOUT 1 /* file descriptor for standard output */
#define STDERR 2 /* file descriptor for standard error */

typedef struct 

{
	unsigned _file;
	unsigned _flag;
	char *_base;
	char *_ptr;
	unsigned _cnt;
}

FILE;

#define _NFILE FOPEN_MAX

extern FILE _iob [_NFILE];

#define stdin    (&_iob[ STDIN]) /* file pointer for standard input */
#define stdout   (&_iob[STDOUT]) /* file pointer for standard output */
#define stderr   (&_iob[STDERR]) /* file pointer for standard error */

#define _IOREAD  0x0001   /* open for read */
#define _IOWRITE 0x0002   /* open for write */
#define _IOUNBUF 0x0004   /* unbuffered I/O */
#define _IOALLOC 0x0008   /* dynamically allocated buffer */
#define _IOEOF   0x0010   /* end of file detected */
#define _IOERR   0x0020   /* error detected */
#define _IOTEXT  0x0040   /* text file with crlf format */
#define _IOPRINT 0x0080   /* (reserved) */
#define _IOFBF   0x0000
#define _IOLBF   0x0040
#define _IONBF   0x0004

#define _fileno(stream)    ((stream)->_file)
#define _clearerr(stream)  ((stream)->_flag  &= ~(_IOERR|_IOEOF))
#define _feof(stream)      (((stream)->_flag &   (_IOEOF)) != 0)
#define _ferror(stream)    (((stream)->_flag &   (_IOERR)) != 0)
#define _fcount(stream)    (stream)->_cnt)

#define getc(stream)   ((--(stream)->_cnt >= 0)?*(stream)->_ptr++ & (0xFF): filbuf(stream))
#define putc(c,stream) ((--(stream)->_cnt >= 0)?*(stream)->_ptr++ = (unsigned)(c)&(0xFF): flsbuf((c),(stream)))

#undef getc
#undef putc

#define _getitem(item) (read(STDIN_FILENO,&item,sizeof(item))<sizeof(item)?EOF:0)
#define _putitem(item) (write(STDOUT_FILENO,&item,sizeof(item))<sizeof(item)?EOF:0)

/*====================================================================*
 *  buffered I/O library function prototypes;
 *--------------------------------------------------------------------*/

FILE *_fopen (char const *pathname, char const *openmode);
FILE *_freopen (char const *pathname, char const *openmode, FILE *stream);
int _dopen (char const *pathname, char const *openmode);
FILE *_fdopen (int fd, char const *omode);
FILE *_fpinit (int fd, char const *omode, FILE *stream);
int _fclose (FILE *stream);
void _exit (int status);
void _setbuf (FILE *stream, char *buffer);
int _setvbuf (FILE *stream, char *buffer, int mode, size_t bufsize);
int _ffill (FILE *stream);
int _fflush (FILE *stream);
int _fillbuf (FILE *stream);
int _filbuf (FILE *stream);
int _flushbuf (int c, FILE *stream);
int _flsbuf (int c, FILE *stream);
size_t _fread (void *buffer, size_t itemsize, size_t count, FILE *stream);
size_t _fwrite (void const *buffer, size_t itemsize, size_t count, FILE *stream);
int _fcopy (FILE *ifp, FILE *ofp, size_t block);
int _fdcopy (int ifd, int ofd, size_t block);

/*====================================================================*
 * basic character and string I/O function prototypes;
 *--------------------------------------------------------------------*/

int _getchar (void);
int _putchar (int c);
int _getc (FILE *stream);
int _fgetc (FILE *stream);
int _putc (int c, FILE *stream);
int _fputc (int c, FILE *stream);
int _ungetc (int c, FILE *stream);
int _fungetc (int c, FILE *stream);
int _fputs (char const *sp, FILE *stream);
int _puts (char const *sp);
char *_fgets (char *sp, size_t count, FILE *stream);
char *_gets (char *sp);

/*====================================================================*
 * formatted string I/O function prototypes;
 *--------------------------------------------------------------------*/

int _printf (char const *format, ...);
void _eprintf (char const *format, ...);
int _vprintf (char const *format, va_list argp);
int _fprintf (FILE *stream, char const *format, ...);
int _vfprintf (FILE *stream, char const *format, va_list argp);
int _sprintf (char const *string, char const *format, ...);
int _vsprintf (char const *string, char const *format, va_list argp);
int _fscanf (FILE *stream, char const *format, ...);
int _sscanf (char const *sp, char const *format, ...);
int _scanf (char const *sp, ...);

/*====================================================================*
 * temporary file/filename function prototypes;
 *--------------------------------------------------------------------*/

FILE *tmpfile (void);
char *_mktemp (char *format);
int _rmtmp (void);
char *tempnam (char *sp, char *path);
char *tmpnam (char *path);

/*====================================================================*
 * file positioning function prototypes;
 *--------------------------------------------------------------------*/

#define SEEK_CUR 1
#define SEEK_END 2
#define SEEK_SET 0

typedef long fpos_t;
int fgetpos (FILE *stream, fpos_t *pos);
int fsetpos (FILE *stream, const fpos_t *pos);
void rewind (FILE *stream);
long fseek (FILE *stream, long offset, long origin);
long ftell (FILE *stream);

/*====================================================================*
 * UNIX/ZENIX low level I/O functions;
 *--------------------------------------------------------------------*/

#include "_fcntl.h"
#include "_io.h"

/*====================================================================*
 *
 *--------------------------------------------------------------------*/

int system (char const *command);
void perror (char const *message);

/*====================================================================*
 * end definitions;
 *--------------------------------------------------------------------*/

#endif

