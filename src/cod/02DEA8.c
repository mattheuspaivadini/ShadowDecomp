/* asm/cod/02DEA8.s -> MINSIZE.
 * Newlib mallocr.c malloc_trim; size_t=32-bit, long=64-bit, .data attr for the sbrk_base global
 * MATCHED. */
typedef unsigned int size_t_02DEA8;   /* size_t in this SDK: 32-bit */

struct S02DEA8_chunk {
    size_t_02DEA8         prev_size;  /* 0x00 */
    size_t_02DEA8         size;       /* 0x04 */
    struct S02DEA8_chunk *fd;         /* 0x08 */
    struct S02DEA8_chunk *bk;         /* 0x0C */
};

struct S02DEA8_mallinfo {
    int arena;      /* 0x00 == sbrked_mem */
    int ordblks;
    int smblks;
    int hblks;
    int hblkhd;
    int usmblks;
    int fsmblks;
    int uordblks;
    int fordblks;
    int keepcost;
};

/* The image reaches these three globals absolutely (`lui`/`%hi`+`%lo`), never
 * `%gp_rel`, so the .data section attribute keeps `-G8` from putting the 4-byte
 * `char *__malloc_sbrk_base` into the small-data window. */
#define D_ABS_02DEA8 __attribute__((section(".data")))

extern struct S02DEA8_chunk     *__malloc_av_[]           D_ABS_02DEA8;
extern struct S02DEA8_mallinfo   __malloc_current_mallinfo D_ABS_02DEA8;
extern char                     *__malloc_sbrk_base        D_ABS_02DEA8;

extern void  __malloc_lock(void *reent);
extern void  __malloc_unlock(void *reent);
extern char *_sbrk_r(void *reent, int incr);

#define MINSIZE            (sizeof(struct S02DEA8_chunk))
#define PREV_INUSE         0x1
#define SIZE_BITS          (PREV_INUSE | 0x2)
#define chunksize(p)       ((p)->size & ~(SIZE_BITS))
#define set_head(p, s)     ((p)->size = (s))
#define malloc_getpagesize (4096)
#define sbrked_mem         (__malloc_current_mallinfo.arena)
#define MORECORE_FAILURE   ((char *)-1)

int _malloc_trim_r(void *ptr, size_t_02DEA8 pad)
{
    long          top_size;
    long          extra;
    char         *current_brk;
    char         *new_brk;
    unsigned long pagesz = malloc_getpagesize;

    __malloc_lock(ptr);

    top_size = chunksize(__malloc_av_[2]);
    extra = ((top_size - pad - MINSIZE + (pagesz - 1)) / pagesz - 1) * pagesz;

    if (extra < (long)pagesz) {         /* Not enough memory to release */
        __malloc_unlock(ptr);
        return 0;
    } else {
        /* Test to make sure no one else called sbrk. */
        current_brk = (char *)_sbrk_r(ptr, 0);
        if (current_brk != (char *)(__malloc_av_[2]) + top_size) {
            __malloc_unlock(ptr);
            return 0;                   /* Apparently we don't own memory */
        } else {
            new_brk = (char *)_sbrk_r(ptr, -extra);

            if (new_brk == MORECORE_FAILURE) {   /* sbrk failed */
                /* Try to figure out what we have */
                current_brk = (char *)_sbrk_r(ptr, 0);
                top_size = current_brk - (char *)(__malloc_av_[2]);
                if (top_size >= (long)MINSIZE) {
                    sbrked_mem = current_brk - __malloc_sbrk_base;
                    set_head(__malloc_av_[2], top_size | PREV_INUSE);
                }
                __malloc_unlock(ptr);
                return 0;
            } else {
                /* Success.  Adjust top accordingly. */
                set_head(__malloc_av_[2], (top_size - extra) | PREV_INUSE);
                sbrked_mem -= extra;
                __malloc_unlock(ptr);
                return 1;
            }
        }
    }
}
