/* asm/cod/02E018.s -> __sfvwrite.
 * Newlib fvwrite.c __sfvwrite (old non-reentrant revision, no asprintf path); COPY -> func_001282CC (memmove)
 * MATCHED. */
typedef unsigned int size_t_02E018;

struct S02E018_sbuf {
    unsigned char *_base;   /* 0x10 */
    int            _size;   /* 0x14 */
};

struct S02E018_FILE {
    unsigned char *_p;                       /* 0x00 */
    int            _r;                       /* 0x04 */
    int            _w;                       /* 0x08 */
    short          _flags;                   /* 0x0C */
    short          _file;                    /* 0x0E */
    struct S02E018_sbuf _bf;                 /* 0x10 */
    int            _lbfsize;                 /* 0x18 */
    void          *_cookie;                  /* 0x1C */
    int          (*_read)(void *, char *, int);        /* 0x20 */
    int          (*_write)(void *, const char *, int); /* 0x24 */
};

struct S02E018_siov {
    const void   *iov_base; /* 0x00 */
    size_t_02E018 iov_len;  /* 0x04 */
};

struct S02E018_suio {
    struct S02E018_siov *uio_iov;    /* 0x00 */
    int                  uio_iovcnt; /* 0x04 */
    int                  uio_resid;  /* 0x08 */
};

extern int   __swsetup(struct S02E018_FILE *fp);
extern int   fflush(struct S02E018_FILE *fp);
extern void *memchr(const void *s, int c, size_t_02E018 n);
extern void *func_001282CC(void *dst, const void *src, size_t_02E018 n);

#define EOF     (-1)
#define BUFSIZ  1024
#define __SLBF  0x0001
#define __SNBF  0x0002
#define __SWR   0x0008
#define __SERR  0x0040
#define __SSTR  0x0200

#define cantwrite(fp) \
	((((fp)->_flags & __SWR) == 0 || (fp)->_bf._base == 0) && \
	 __swsetup(fp))

#define	MIN(a, b) ((a) < (b) ? (a) : (b))
#define	COPY(n)	  (void) func_001282CC ((void *) fp->_p, (void *) p, (size_t_02E018) (n))

#define GETIOV(extra_work) \
  while (len == 0) \
    { \
      extra_work; \
      p = iov->iov_base; \
      len = iov->iov_len; \
      iov++; \
    }

int __sfvwrite(register struct S02E018_FILE *fp, register struct S02E018_suio *uio)
{
  register size_t_02E018 len;
  register const char *p;
  register struct S02E018_siov *iov;
  register int w, s;
  char *nl;
  int nlknown, nldist;

  if ((len = uio->uio_resid) == 0)
    return 0;

  /* make sure we can write */
  if (cantwrite (fp))
    return EOF;

  iov = uio->uio_iov;
  len = 0;
  if (fp->_flags & __SNBF)
    {
      /*
       * Unbuffered: write up to BUFSIZ bytes at a time.
       */
      do
	{
	  GETIOV (;);
	  w = (*fp->_write) (fp->_cookie, p, MIN (len, BUFSIZ));
	  if (w <= 0)
	    goto err;
	  p += w;
	  len -= w;
	}
      while ((uio->uio_resid -= w) != 0);
    }
  else if ((fp->_flags & __SLBF) == 0)
    {
      /*
       * Fully buffered: fill partially full buffer, if any,
       * and then flush.  If there is no partial buffer, write
       * one _bf._size byte chunk directly (without copying).
       *
       * String output is a special case: write as many bytes
       * as fit, but pretend we wrote everything.
       */
      do
	{
	  GETIOV (;);
	  w = fp->_w;
	  if (fp->_flags & __SSTR)
	    {
	      if (len < w)
		w = len;
	      COPY (w);		/* copy MIN(fp->_w,len), */
	      fp->_w -= w;
	      fp->_p += w;
	      w = len;		/* but pretend copied all */
	    }
	  else if (fp->_p > fp->_bf._base && len > w)
	    {
	      /* fill and flush */
	      COPY (w);
	      /* fp->_w -= w; *//* unneeded */
	      fp->_p += w;
	      if (fflush (fp))
		goto err;
	    }
	  else if (len >= (w = fp->_bf._size))
	    {
	      /* write directly */
	      w = (*fp->_write) (fp->_cookie, p, w);
	      if (w <= 0)
		goto err;
	    }
	  else
	    {
	      /* fill and done */
	      w = len;
	      COPY (w);
	      fp->_w -= w;
	      fp->_p += w;
	    }
	  p += w;
	  len -= w;
	}
      while ((uio->uio_resid -= w) != 0);
    }
  else
    {
      /*
       * Line buffered: like fully buffered, but we
       * must check for newlines.
       */
      nlknown = 0;
      do
	{
	  GETIOV (nlknown = 0);
	  if (!nlknown)
	    {
	      nl = memchr ((void *) p, '\n', len);
	      nldist = nl ? nl + 1 - p : len + 1;
	      nlknown = 1;
	    }
	  s = MIN (len, nldist);
	  w = fp->_w + fp->_bf._size;
	  if (fp->_p > fp->_bf._base && s > w)
	    {
	      COPY (w);
	      /* fp->_w -= w; */
	      fp->_p += w;
	      if (fflush (fp))
		goto err;
	    }
	  else if (s >= (w = fp->_bf._size))
	    {
	      w = (*fp->_write) (fp->_cookie, p, w);
	      if (w <= 0)
		goto err;
	    }
	  else
	    {
	      w = s;
	      COPY (w);
	      fp->_w -= w;
	      fp->_p += w;
	    }
	  if ((nldist -= w) == 0)
	    {
	      /* copied the newline: flush and forget */
	      if (fflush (fp))
		goto err;
	      nlknown = 0;
	    }
	  p += w;
	  len -= w;
	}
      while ((uio->uio_resid -= w) != 0);
    }
  return 0;

err:
  fp->_flags |= __SERR;
  return EOF;
}
