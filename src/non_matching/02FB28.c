/* STATUS (Session 7, 2026-10-14): NON_MATCHING. best score 12 [cc=296, default].
 * worker + conditional field update.
 * The original .s stays in the build (asm/cod/02FB28.s); this C
 * draft (subagent-produced, Session 7) is kept for the record. */
/* asm/cod/02FB28.s -> func_0012FB28 @ 0x0012FB28 (0x64 bytes, 25 insns)
 *
 * Companion of func_0012FA40 on the same stdio-family state block: run the
 * worker and, when it reports -1, clear the 0x1000 status bit; otherwise record
 * its value in p->f50 and set the bit:
 *
 *   r = func_001311B8(p->f54, p->f0E, a1, a2);   ; a3 = a2, a2 = a1
 *   if (r == -1)
 *       p->f0C &= 0xEFFF;                        ; lhu/andi/sh
 *   else {
 *       p->f50 = r;                              ; sw
 *       p->f0C |= 0x1000;                        ; ori
 *   }
 *
 * Nothing is returned ($v0 keeps the callee's value).  The
 * `dsll32 $a1,$v1,0` + `dsra32 $a1,$a1,0` after the call is the Session-7
 * sign-extend pattern (probe g11, build/s7/probe_ext3.c): the worker must be
 * declared as returning a **64-bit** type while this wrapper uses it as an
 * `int` - all three call sites of func_001311B8/func_00131218 in the image
 * narrow the result right after the call.  The raw word is what the `-1` test
 * compares (`daddu $v1,$v0,` then `bne`), the extended copy is what gets
 * stored.
 * MATCH GUESS: cc=296
 * RESIDUAL (UNCONFIRMED): the exact source split between the raw compare and
 * the extended store (two `int`s vs one) could not be pinned down from the asm;
 * if the pair lands in the compare register instead of $a1, the store is the
 * narrowing and the test uses the plain low word. */
struct S12FB28 {
    char pad00[0x0C];
    unsigned short f0C;             /* 0x0C status word, bit 0x1000 toggled */
    short f0E;                      /* 0x0E signed halfword argument        */
    char pad10[0x40];
    int f50;                        /* 0x50 value reported by the worker     */
    int f54;                        /* 0x54 handle passed to the worker      */
};

long long func_001311B8(int a0, int a1, int a2, int a3);

void func_0012FB28(struct S12FB28 *p, int a1, int a2) {
    long long q = func_001311B8(p->f54, p->f0E, a1, a2);
    int r = q;

    if (r == -1)
        p->f0C &= 0xEFFF;
    else {
        p->f50 = r;
        p->f0C |= 0x1000;
    }
}
