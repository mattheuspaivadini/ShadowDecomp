/* STATUS (10, 2026-10-16): NON_MATCHING. best score 13 [cc=296].
 * 
 * The original .s stays in the build (asm/cod/031048.s); this C
 * draft (10) is kept for the record. */
typedef unsigned int size_t;
typedef unsigned int INTERNAL_SIZE_T;

struct malloc_chunk {
    INTERNAL_SIZE_T prev_size;
    INTERNAL_SIZE_T size;
    struct malloc_chunk *fd;
    struct malloc_chunk *bk;
};
typedef struct malloc_chunk *mchunkptr;

extern void *_malloc_r(void *reent, size_t sz);
extern void *func_001283D0(void *s, int c, size_t n);

void *_calloc_r(void *reent, size_t n, size_t elem_size) {
    mchunkptr p;
    INTERNAL_SIZE_T csz;
    INTERNAL_SIZE_T sz = n * elem_size;
    void *mem = _malloc_r(reent, sz);

    if (mem == 0) {
        return 0;
    } else {
        INTERNAL_SIZE_T mzsz;
        p = (mchunkptr)((char *)mem - 2 * sizeof(INTERNAL_SIZE_T));
        csz = p->size & ~(INTERNAL_SIZE_T)3;
        mzsz = csz - sizeof(INTERNAL_SIZE_T);
        if (mzsz <= 9 * sizeof(mzsz)) {
            INTERNAL_SIZE_T *mz = (INTERNAL_SIZE_T *)mem;
            if (mzsz >= 5 * sizeof(mzsz)) {
                *mz++ = 0;
                *mz++ = 0;
                if (mzsz >= 7 * sizeof(mzsz)) {
                    *mz++ = 0;
                    *mz++ = 0;
                    if (mzsz >= 9 * sizeof(mzsz)) {
                        *mz++ = 0;
                        *mz++ = 0;
                    }
                }
            }
            *mz++ = 0;
            *mz++ = 0;
            *mz = 0;
        } else {
            func_001283D0(mem, 0, mzsz);
        }
        return mem;
    }
}
