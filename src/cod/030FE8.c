/* asm/cod/030FE8.s -> _write_r.
 * Newlib 1.9.0 reent/writer.c _write_r (authentic source; SCE write returns int)
 * MATCHED. */
#include "newlib19.h"

/* We use the errno variable used by the system dependent layer.  */
extern int errno NL19_DATA;

extern int write (int, const void *, size_t);
#define _write write

long
_write_r (struct _reent *ptr, int fd, const void *buf, size_t cnt)
{
  long ret;

  errno = 0;
  if ((ret = _write (fd, buf, cnt)) == -1 && errno != 0)
    ptr->_errno = errno;
  return ret;
}
