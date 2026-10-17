/* asm/cod/029830.s -> if.
 * Newlib 1.9.0 stdio/vfprintf.c static __sprint (authentic source)
 * MATCHED. */
#include "newlib19.h"
#include <stdarg.h>

/* newlib/libc/stdio/fvwrite.h */
struct __siov {
	const void *    iov_base;
	size_t	iov_len;
};
struct __suio {
	struct	__siov *uio_iov;
	int	uio_iovcnt;
	int	uio_resid;
};

extern int __sfvwrite(FILE *, struct __suio *);

#define __sprint func_00129830

int
__sprint(fp, uio)
	FILE *fp;
	register struct __suio *uio;
{
	register int err;

	if (uio->uio_resid == 0) {
		uio->uio_iovcnt = 0;
		return (0);
	}
	err = __sfvwrite(fp, uio);
	uio->uio_resid = 0;
	uio->uio_iovcnt = 0;
	return (err);
}
