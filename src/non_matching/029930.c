/* STATUS (14, 2026-10-16): NON_MATCHING. best score 14 [cc=296].
 * vfprintf wrapper: 29/29 insns, frame 0x20 (fp->_data reloaded for the tail call); residual = s1/s2 swapped (mine s1=ap, orig s1=fmt) + branch-likely bit on the __sdidinit test
 * The original .s stays in the build (asm/cod/029930.s); this C
 * draft (14) is kept for the record. */
#include "symbols.h"

struct S029930_reent {
    char _pad0[0x38];
    int  __sdidinit;               /* 0x38 */
};

struct S029930_FILE {
    char _pad0[0x54];
    struct S029930_reent *_data;   /* 0x54 */
};

extern void __sinit(struct S029930_reent *ptr);
extern int _vfprintf_r(struct S029930_reent *ptr, struct S029930_FILE *fp,
                       const char *fmt, char *ap);

int func_00129930(struct S029930_FILE *fp, const char *fmt, char *ap)
{
    struct S029930_reent *ptr;

    ptr = fp->_data;
    if (ptr == 0)
        ptr = fp->_data = (struct S029930_reent *)_impure_ptr;
    if (ptr->__sdidinit == 0)
        __sinit(ptr);
    return _vfprintf_r(fp->_data, fp, fmt, ap);
}
