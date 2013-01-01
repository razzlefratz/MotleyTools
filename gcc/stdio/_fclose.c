/*====================================================================*
 *
 *   FILE *_fclose(FILE *fp);
 *
 *   _stdio.h
 *
 *   close the file control block references by a file pointer and free
 *   the block for reuse; flush any buffered output data; return NULL on
 *   success or EOF on failure;
 *
 *   a provision has been made for Microsoft MSDOS 1.0 which requires
 *   that an ASCII SUB character terminate all text files; this feature
 *   is, of course, no longer required;
 *
 *.  Motley Tools by Charles Maier
 *:  Published 1982-2005 by Charles Maier for personal use
 *;  Licensed under the Internet Software Consortium License
 *
 *--------------------------------------------------------------------*/

#include "_stdio.h"

int _fclose (register FILE *fp) 

{
	if ((fp != NULL) && ((fp->_flag & (_IOREAD|_IOWRITE)) != 0)) 
	{
		if ((fp->_flag & (_IOWRITE)) != 0) if (_fflush (fp) == EOF) return (EOF);

#ifdef _MSDOS

		char c = '004';
		if ((fp->_flag & (_IOWRITE)) != 0) write (fp->_file, &c, 1);

#endif

		if (_close (fp->_file) != ERR) 
		{
			if ((fp->_flag & (_IOALLOC)) != 0) free (fp->_base);
			fp->_file = 0;
			fp->_flag = 0;
			fp->_ptr = fp->_base = NULL;
			fp->_cnt = 0;
			return (0);
		}
	}
	return (EOF);
}

