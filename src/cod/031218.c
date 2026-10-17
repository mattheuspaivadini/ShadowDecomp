/* asm/cod/031218.s -> _read_r.
 * Newlib 1.9.0 reent/readr.c _read_r (authentic source; SCE read returns int)
 * MATCHED. */
#include "newlib19.h"

/* We use the errno variable used by the system dependent layer.  */
extern int errno NL19_DATA;

extern int read (int, void *, size_t);
#define _read read

long
_read_r (struct _reent *ptr, int fd, void *buf, size_t cnt)
{
  long ret;

  errno = 0;
  if ((ret = _read (fd, buf, cnt)) == -1 && errno != 0)
    ptr->_errno = errno;
  return ret;
}
