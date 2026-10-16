/* asm/cod/02E578.s -> __smakebuf.
 * Newlib makebuf.c __smakebuf; stat frame size adapted to the original 0x90/0x70 layout
 * MATCHED. */
#define BUFSIZ   0x400

#define __SLBF   0x0001
#define __SNBF   0x0002
#define __SMBF   0x0080
#define __SOPT   0x0400
#define __SNPT   0x0800

#define S_IFMT   0xF000
#define S_IFCHR  0x2000
#define S_IFREG  0x8000

struct S02E578_sbuf {
    unsigned char *_base;   /* +0x00 */
    int            _size;   /* +0x04 */
};

struct S02E578_reent {
    char _pad0[0x3C];
    void (*__cleanup)(struct S02E578_reent *);   /* 0x3C */
};

typedef struct S02E578_FILE {
    unsigned char          *_p;        /* 0x00 */
    int                     _r;        /* 0x04 */
    int                     _w;        /* 0x08 */
    short                   _flags;    /* 0x0C */
    short                   _file;     /* 0x0E */
    struct S02E578_sbuf     _bf;       /* 0x10 */
    int                     _lbfsize;  /* 0x18 */
    void                   *_cookie;   /* 0x1C */
    int                   (*_read)(void *, char *, int);          /* 0x20 */
    int                   (*_write)(void *, const char *, int);   /* 0x24 */
    int                   (*_seek)(void *, int, int);             /* 0x28 */
    int                   (*_close)(void *);                      /* 0x2C */
    struct S02E578_sbuf     _ub;       /* 0x30 */
    unsigned char          *_up;       /* 0x38 */
    int                     _ur;       /* 0x3C */
    unsigned char           _ubuf[3];  /* 0x40 */
    unsigned char           _nbuf[1];  /* 0x43 */
    struct S02E578_sbuf     _lb;       /* 0x44 */
    int                     _blksize;  /* 0x4C */
    int                     _offset;   /* 0x50 */
    struct S02E578_reent   *_data;     /* 0x54 */
} FILE;

struct S02E578_stat {
    int  _st_dev;     /* 0x00 */
    int  st_mode;     /* 0x04 */
    char _pad[0x64];  /* see the frame note above */
};

extern int __sseek();
extern void _cleanup_r(struct S02E578_reent *ptr);
extern int _fstat_r(struct S02E578_reent *ptr, int fd, struct S02E578_stat *st);
extern void *_malloc_r(struct S02E578_reent *ptr, unsigned int size);
extern int isatty(int fd);

void __smakebuf(FILE *fp)
{
    unsigned int size, couldbetty;
    void *p;
    struct S02E578_stat st;

    if (fp->_flags & __SNBF) {
        fp->_bf._base = fp->_p = fp->_nbuf;
        fp->_bf._size = 1;
        return;
    }
    if (fp->_file < 0 || _fstat_r(fp->_data, fp->_file, &st) < 0) {
        couldbetty = 0;
        size = BUFSIZ;
        fp->_flags |= __SNPT;
    } else {
        couldbetty = (st.st_mode & S_IFMT) == S_IFCHR;
        size = BUFSIZ;
        if ((st.st_mode & S_IFMT) == S_IFREG && fp->_seek == __sseek) {
            fp->_blksize = 1024;
            fp->_flags |= __SOPT;
        } else
            fp->_flags |= __SNPT;
    }
    if ((p = _malloc_r(fp->_data, size)) == 0) {
        fp->_flags |= __SNBF;
        fp->_bf._base = fp->_p = fp->_nbuf;
        fp->_bf._size = 1;
    } else {
        fp->_data->__cleanup = _cleanup_r;
        fp->_flags |= __SMBF;
        fp->_bf._base = fp->_p = (unsigned char *)p;
        fp->_bf._size = size;
        if (couldbetty && isatty(fp->_file))
            fp->_flags |= __SLBF;
    }
}
