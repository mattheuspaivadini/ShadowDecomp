/* newlib19.h - the Newlib 1.9.0 stdio/reent definitions this image was built with.
 *
 * Transcribed from newlib-1_9_0 (sourceware newlib-cygwin.git, tag newlib-1_9_0):
 * newlib/libc/include/sys/reent.h, newlib/libc/include/stdio.h and
 * newlib/libc/stdio/local.h. Evidence that this is the right revision: the image's
 * __sfvwrite (02E018) is the old non-reentrant `(*fp->_write)(fp->_cookie, ...)'
 * form, and __submore (030D78) reads the reent from fp->_data at 0x54, both as in
 * newlib-1_9_0.
 *
 * Type model of this EE-GCC build (docs/compiler.md section 8): int and pointers
 * are 4 bytes, long is 8 bytes, size_t is 4 bytes. So _fpos_t (= long) is 64-bit.
 *
 * Globals the image reaches absolutely (`lui'/%hi+%lo) carry NL19_DATA so -G8 does
 * not move them into the small-data window. */
#ifndef NEWLIB19_H
#define NEWLIB19_H

#define NL19_DATA __attribute__((section(".data")))

typedef unsigned int size_t;
typedef long _fpos_t;
typedef _fpos_t fpos_t;
typedef long _off_t;
typedef _off_t off_t;
typedef long _ssize_t;

#ifndef NULL
#define NULL 0
#endif

#define _ATEXIT_SIZE 32

struct _atexit {
	struct	_atexit *_next;			/* next in list */
	int	_ind;				/* next index in this table */
	void	(*_fns[_ATEXIT_SIZE])(void);	/* the table itself */
};

struct __sbuf {
	unsigned char *_base;
	int	_size;
};

struct _reent;

struct __sFILE {
  unsigned char *_p;	/* 0x00 current position in (some) buffer */
  int	_r;		/* 0x04 read space left for getc() */
  int	_w;		/* 0x08 write space left for putc() */
  short	_flags;		/* 0x0C flags, below; this FILE is free if 0 */
  short	_file;		/* 0x0E fileno, if Unix descriptor, else -1 */
  struct __sbuf _bf;	/* 0x10 the buffer (at least 1 byte, if !NULL) */
  int	_lbfsize;	/* 0x18 0 or -_bf._size, for inline putc */

  /* operations */
  void *_cookie;	/* 0x1C cookie passed to io functions */

  int	(*_read)(void *_cookie, char *_buf, int _n);			/* 0x20 */
  int	(*_write)(void *_cookie, const char *_buf, int _n);		/* 0x24 */
  _fpos_t (*_seek)(void *_cookie, _fpos_t _offset, int _whence);	/* 0x28 */
  int	(*_close)(void *_cookie);					/* 0x2C */

  /* separate buffer for long sequences of ungetc() */
  struct __sbuf _ub;	/* 0x30 ungetc buffer */
  unsigned char *_up;	/* 0x38 saved _p when _p is doing ungetc data */
  int	_ur;		/* 0x3C saved _r when _r is counting ungetc data */

  /* tricks to meet minimum requirements even when malloc() fails */
  unsigned char _ubuf[3];	/* 0x40 guarantee an ungetc() buffer */
  unsigned char _nbuf[1];	/* 0x43 guarantee a getc() buffer */

  /* separate buffer for fgetline() when line crosses buffer boundary */
  struct __sbuf _lb;	/* 0x44 buffer for fgetline() */

  /* Unix stdio files get aligned to block boundaries on fseek() */
  int	_blksize;	/* 0x4C stat.st_blksize (may be != _bf._size) */
  int	_offset;	/* 0x50 current lseek offset */

  struct _reent *_data;	/* 0x54 */
};

typedef struct __sFILE FILE;

struct _glue
{
  struct _glue *_next;
  int _niobs;
  struct __sFILE *_iobs;
};

struct tm
{
  int	tm_sec;
  int	tm_min;
  int	tm_hour;
  int	tm_mday;
  int	tm_mon;
  int	tm_year;
  int	tm_wday;
  int	tm_yday;
  int	tm_isdst;
};

struct _reent
{
  /* local copy of errno */
  int _errno;

  struct __sFILE *_stdin, *_stdout, *_stderr;

  int  _inc;			/* used by tmpnam */
  char _emergency[25];

  int _current_category;	/* used by setlocale */
  const char *_current_locale;

  int __sdidinit;		/* 1 means stdio has been init'd */

  void (*__cleanup)(struct _reent *);

  /* used by mprec routines */
  struct _Bigint *_result;
  int _result_k;
  struct _Bigint *_p5s;
  struct _Bigint **_freelist;

  /* used by some fp conversion routines */
  int _cvtlen;			/* should be size_t */
  char *_cvtbuf;

  union
    {
      struct
        {
          unsigned int _unused_rand;
          char * _strtok_last;
          char _asctime_buf[26];
          struct tm _localtime_buf;
          int _gamma_signgam;
          __extension__ unsigned long long _rand_next;

        } _reent;
#define _N_LISTS 30
      struct
        {
          unsigned char * _nextf[_N_LISTS];
          unsigned int _nmalloc[_N_LISTS];
        } _unused;
    } _new;

  /* atexit stuff */
  struct _atexit *_atexit;	/* points to head of LIFO stack */
  struct _atexit _atexit0;	/* one guaranteed table, required by ANSI */

  /* signal info */
  void (**(_sig_func))(int);

  /* These are here last so that __sFILE can grow without changing the offsets
     of the above members (on the off chance that future binary compatibility
     would be broken otherwise).  */
  struct _glue __sglue;			/* root of glue chain */
  struct __sFILE __sf[3];		/* first three file descriptors */
};

extern struct _reent *_impure_ptr NL19_DATA;
#define _REENT _impure_ptr
#define _stdin_r(x)	((x)->_stdin)
#define _stdout_r(x)	((x)->_stdout)
#define _stderr_r(x)	((x)->_stderr)

#define	__SLBF	0x0001		/* line buffered */
#define	__SNBF	0x0002		/* unbuffered */
#define	__SRD	0x0004		/* OK to read */
#define	__SWR	0x0008		/* OK to write */
	/* RD and WR are never simultaneously asserted */
#define	__SRW	0x0010		/* open for reading & writing */
#define	__SEOF	0x0020		/* found EOF */
#define	__SERR	0x0040		/* found error */
#define	__SMBF	0x0080		/* _buf is from malloc */
#define	__SAPP	0x0100		/* fdopen()ed in append mode - so must  write to end */
#define	__SSTR	0x0200		/* this is an sprintf/snprintf string */
#define	__SOPT	0x0400		/* do fseek() optimisation */
#define	__SNPT	0x0800		/* do not do fseek() optimisation */
#define	__SOFF	0x1000		/* set iff _offset is in fact correct */
#define	__SMOD	0x2000		/* true => fgetline modified _p text */

#define	_IOFBF	0		/* setvbuf should set fully buffered */
#define	_IOLBF	1		/* setvbuf should set line buffered */
#define	_IONBF	2		/* setvbuf should set unbuffered */

#define	EOF	(-1)
#define	BUFSIZ	1024

#define	SEEK_SET	0	/* set file offset to offset */
#define	SEEK_CUR	1	/* set file offset to current plus offset */
#define	SEEK_END	2	/* set file offset to EOF plus offset */

/* newlib/libc/stdio/local.h */
extern FILE  *__sfp(struct _reent *);
extern int    __sflags(struct _reent *, const char*, int*);
extern int    __srefill(FILE *);
extern int    __sread(void *, char *, int);
extern int    __swrite(void *, char const *, int);
extern fpos_t __sseek(void *, fpos_t, int);
extern int    __sclose(void *);
extern void   __sinit(struct _reent *);
extern void   _cleanup_r(struct _reent *);
extern void   __smakebuf(FILE *);
extern int    _fwalk(struct _reent *, int (*)(FILE *));
extern struct _glue *__sfmoreglue(struct _reent *, int n);
extern int    __swsetup(FILE *);
extern int    fflush(FILE *);

/* newlib/libc/include/reent.h (the _r syscall layer) */
extern _off_t   _lseek_r(struct _reent *, int, _off_t, int);
extern _ssize_t _write_r(struct _reent *, int, const void *, size_t);
extern _ssize_t _read_r(struct _reent *, int, void *, size_t);
extern int      _close_r(struct _reent *, int);

/* The image's memcpy/memset/memmove are known only by their splat labels
 * (config/symbol_addrs.txt records the identification in comments). */
extern void *func_0012821C(void *, const void *, size_t);	/* memcpy */
extern void *func_001282CC(void *, const void *, size_t);	/* memmove */
extern void *func_001283D0(void *, int, size_t);		/* memset */

extern void  *_malloc_r(struct _reent *, size_t);
extern void  *_realloc_r(struct _reent *, void *, size_t);
extern void   _free_r(struct _reent *, void *);

#define CHECK_INIT(fp) \
  do					\
    {					\
      if ((fp)->_data == 0)		\
	(fp)->_data = _REENT;		\
      if (!(fp)->_data->__sdidinit)	\
	__sinit ((fp)->_data);		\
    }					\
  while (0)

#define	cantwrite(fp) \
  ((((fp)->_flags & __SWR) == 0 || (fp)->_bf._base == NULL) && \
   __swsetup(fp))

#define	HASUB(fp) ((fp)->_ub._base != NULL)
#define	FREEUB(fp) { \
	if ((fp)->_ub._base != (fp)->_ubuf) \
		_free_r(fp->_data, (char *)(fp)->_ub._base); \
	(fp)->_ub._base = NULL; \
}

#define	HASLB(fp) ((fp)->_lb._base != NULL)
#define	FREELB(fp) { _free_r(fp->_data,(char *)(fp)->_lb._base); (fp)->_lb._base = NULL; }

#define	NDYNAMIC 4	/* add four more whenever necessary */

#endif /* NEWLIB19_H */
