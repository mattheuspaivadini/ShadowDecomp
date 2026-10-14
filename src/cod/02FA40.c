/* asm/cod/02FA40.s -> func_0012FA40 @ 0x0012FA40 (0x64 bytes, 25 insns)
 *
 * Stream/offset update of the 0x12F8xx-0x12FBxx stdio-family state block:
 *
 *   r = func_00131218(p->f54, p->f0E, a1, a2);   ; a3 = a2, a2 = a1
 *   if (r >= 0)
 *       p->f50 += r;                             ; lw/addu/sw
 *   else
 *       p->f0C &= 0xEFFF;                        ; lhu/andi 0xEFFF/sh
 *   return r;
 *
 * The argument shuffle (`$a3 = $a2`, `$a2 = $a1`, `$a0 = p->0x54`, `$a1 =
 * (short)p->0x0E`) happens before the call, so $s0 is only the block pointer.
 * The `dsll32 $a0,$v0,0` + `dsra32 $a0,$a0,0` right after the call is the
 * Session-7 sign-extend pattern: the callee must be declared as returning a
 * 64-bit type while this wrapper uses the value as `int` (probe g11,
 * build/s7/probe_ext3.c) - the same trick that made 027500 byte-exact.  The
 * negative arm is out of line, so the `if (r >= 0)` form is the fall-through.
 * MATCH GUESS: cc=296 (p->f0E is `lh`, i.e. a signed short field) */
struct S12FA40 {
    char pad00[0x0C];
    unsigned short f0C;             /* 0x0C status word, bit 0x1000 toggled */
    short f0E;                      /* 0x0E signed halfword argument        */
    char pad10[0x40];
    int f50;                        /* 0x50 accumulated value               */
    int f54;                        /* 0x54 handle passed to the worker     */
};

long long func_00131218(int a0, int a1, int a2, int a3);

int func_0012FA40(struct S12FA40 *p, int a1, int a2) {
    int r = func_00131218(p->f54, p->f0E, a1, a2);

    if (r >= 0)
        p->f50 += r;
    else
        p->f0C &= 0xEFFF;
    return r;
}
