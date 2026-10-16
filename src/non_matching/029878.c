/* STATUS (10, 2026-10-16): NON_MATCHING. best score 2 [cc=296].
 * 
 * The original .s stays in the build (asm/cod/029878.s); this C
 * draft (10) is kept for the record. */
struct _sbuf {
    unsigned char *_base;
    int _size;
};

typedef struct __sFILE {
    unsigned char *_p;
    int _r;
    int _w;
    short _flags;
    short _file;
    struct _sbuf _bf;
    int _lbfsize;
    void *_cookie;
    int (*_read)(void *, char *, int);
    int (*_write)(void *, const char *, int);
    int (*_seek)(void *, int, int);
    int (*_close)(void *);
    struct _sbuf _ub;
    unsigned char *_up;
    int _ur;
    unsigned char _ubuf[3];
    unsigned char _nbuf[1];
    struct _sbuf _lb;
    int _blksize;
    int _offset;
    void *_data;
} FILE;

extern int func_00129930(FILE *fp, const char *fmt, void *ap);
extern int fflush(FILE *fp);

int func_00129878(FILE *fp, const char *fmt, void *ap) {
    int ret;
    FILE fake;
    unsigned char buf[1024];

    fake._flags = fp->_flags & ~2;
    fake._file = fp->_file;
    fake._data = fp->_data;
    fake._cookie = fp->_cookie;
    fake._write = fp->_write;

    fake._bf._base = fake._p = buf;
    fake._bf._size = fake._w = sizeof(buf);
    fake._lbfsize = 0;

    ret = func_00129930(&fake, fmt, ap);
    if (ret >= 0 && fflush(&fake)) {
        ret = -1;
    }
    if (fake._flags & 0x40) {
        fp->_flags |= 0x40;
    }
    return ret;
}
