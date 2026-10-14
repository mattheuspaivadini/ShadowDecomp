/* asm/cod/00FB88.s -> func_0010FB88 @ 0x0010FB88 (0x60 bytes, 24 insns)
 *
 * Create two synchronized objects (func_00106FE0 is `addiu $v1,$zero,0x40;
 * syscall 0` = CreateSema(param)) whose 0x20-byte parameter blocks carry the
 * table address in the 0x14 field, and publish the two handles:
 *   a.max = 1; a.init = 1; a.option = D_00138250;
 *   b.max = 1; b.init = 1; b.option = D_00138260;
 *   D_001329A0 = func_00106FE0(&a);
 *   D_001329A4 = func_00106FE0(&b);
 * (field offsets: 0x04 and 0x08 are the two `1`s, 0x14 the pointer; the two
 * blocks are 0x20 bytes each, at sp+0x00 and sp+0x20, $ra at 0x40, frame 0x50.)
 * The two result stores are lui/%lo (non-small scalars) and the second one lands
 * in the second call's delay slot. The emission order is 0x14, 0x28, 0x34, 0x04,
 * 0x08, 0x24 - the scheduler interleaves the two blocks' stores, so the exact
 * source statement order could not be recovered; this draft uses the natural
 * block-by-block order. The frame is consistent with either compiler.
 * MATCH GUESS: cc=296 (the neighbouring matched 00FBE8 is a 296 TU) */
struct S00FB88 {
    int   f00;      /* 0x00 */
    int   f04;      /* 0x04 */
    int   f08;      /* 0x08 */
    int   f0C;      /* 0x0C */
    int   f10;      /* 0x10 */
    void *f14;      /* 0x14 */
    char  pad18[8]; /* 0x18 */
};

extern int D_00138250[];   /* lui/%lo: the address is what gets stored */
extern int D_00138260[];
extern __attribute__((section(".data"))) int D_001329A0;   /* non-small scalar */
extern __attribute__((section(".data"))) int D_001329A4;   /* non-small scalar */
extern int func_00106FE0(void *param);

void func_0010FB88(void) {
    struct S00FB88 a;
    struct S00FB88 b;

    a.f04 = 1;
    a.f08 = 1;
    a.f14 = D_00138250;
    b.f04 = 1;
    b.f08 = 1;
    b.f14 = D_00138260;
    D_001329A0 = func_00106FE0(&a);
    D_001329A4 = func_00106FE0(&b);
}
