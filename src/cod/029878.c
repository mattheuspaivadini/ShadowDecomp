/* asm/cod/029878.s -> 029878.
 * Newlib 1.9.0 stdio/vfprintf.c static __sbprintf (authentic source)
 * MATCHED. */
#include "newlib19.h"
#include <stdarg.h>

extern int func_00129930 (FILE *, const char *, va_list);	/* vfprintf (029930) */
#define VFPRINTF func_00129930
#define __sbprintf func_00129878

int
__sbprintf(fp, fmt, ap)
	register FILE *fp;
	const char *fmt;
	va_list ap;
{
	int ret;
	FILE fake;
	unsigned char buf[BUFSIZ];

	/* copy the important variables */
	fake._data = fp->_data;
	fake._flags = fp->_flags & ~__SNBF;
	fake._file = fp->_file;
	fake._cookie = fp->_cookie;
	fake._write = fp->_write;

	/* set up the buffer */
	fake._bf._base = fake._p = buf;
	fake._bf._size = fake._w = sizeof(buf);
	fake._lbfsize = 0;	/* not actually used, but Just In Case */

	/* do the work, then copy any error status */
	ret = VFPRINTF(&fake, fmt, ap);
	if (ret >= 0 && fflush(&fake))
		ret = EOF;
	if (fake._flags & __SERR)
		fp->_flags |= __SERR;
	return (ret);
}
