/* KERNEL.XFF @ 0x00D988 (64 B) - iosMmColToFvecMvec   [MATCH: -G0]
 * Evidence: `ld $v0,0($a1)` / `ld $v1,8($a1)` load the source quad into two
 * GPRs; the same pair is stored TWICE (`sd $v0,0x20($sp)` + `sd $v1,0x28($sp)`
 * and `sd $v0,0($sp)` + `sd $v1,8($sp)`), i.e. two 16-byte copies of `*s` into
 * two stack slots, one of which (+0x00) is never read.  Then
 * `lq $v0,0x20($sp)` / `psrlw $v0,$v0,8` (one MMI asm: this gcc rejects vector
 * shifts) and `sq $v0,0x10($sp)` into the third slot, which is passed to
 * iosITOF15Vector (`$a1 = $sp+0x10`, `$a0` keeps the caller's first argument).
 * Lever: (a) copying the two halves through named `long` locals (`hi` first in
 * the declaration, `lo`), which makes gcc load lo/hi forward into $v0/$v1 and
 * store them forward - a plain `f.v.v = *s` block copy is emitted back to front
 * (hi first) because it may alias; (b) the `sq` must be a *plain 128-bit store*
 * (`f.r.q = q`) - dbr will not move a volatile asm into the jal delay slot -
 * and the argument pointer is materialised before it by an empty asm, so the
 * scheduler's `addiu $a1,$sp,0x10` precedes the jal and `sq` fills the slot.
 * UNCONFIRMED: prototype/argument order of iosITOF15Vector; the names of the
 * three 16-byte stack slots (v/r/u) and the fact that the +0x00 copy is dead.
 */
typedef unsigned int u_long128 __attribute__((mode(TI)));
typedef struct { long lo, hi; } Mvec;
typedef union { Mvec v; u_long128 q; long a[2]; } MV;

void iosITOF15Vector(void *d, void *s);

typedef struct { MV v; MV r; MV u; } Frame;

void iosMmColToFvecMvec(void *d, MV *s) {
    Frame f;
    long hi = s->v.hi, lo = s->v.lo;

    f.v.v.lo = lo;
    f.v.v.hi = hi;
    f.u.v.lo = lo;
    f.u.v.hi = hi;
    {
        u_long128 q;
        MV *p;

        __asm__ __volatile__("lq %0, %1\n"
                             "psrlw %0, %0, 8"
                             : "=&r"(q) : "m"(f.u) : "memory");
        p = &f.r;
        __asm__ ("" : : "r"(p));
        f.r.q = q;
        iosITOF15Vector(d, p);
    }
}
