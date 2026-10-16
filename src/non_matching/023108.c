/* STATUS (Session 7, 2026-10-14): NON_MATCHING. best score 14 [cc=296, default].
 * round-up + 4-word block + two calls.
 * The original .s stays in the build (asm/cod/023108.s); this C
 * draft (subagent-produced, Session 7) is kept for the record. */
/* asm/cod/023108.s -> func_00123108 @ 0x00123108 (0x50 bytes, 20 insns)
 *
 * Blocking syscall pair: func_00107260(0) (syscall 0x64) then
 * func_001073A0(&args, 1) (syscall 0x77), exactly as in the
 * LoaderSysLoadIopModule helper (src/non_matching/002D70.c), whose result is
 * returned here.
 *
 *   size = a2 rounded up to a 0x40 multiple
 *   args = { a0, a1, size, 0 }
 *
 * The rounding is NOT written as `(a2 + 0x3F) & ~0x3F`: the original is
 * `andi 0x3F` first, then `and 0xFFFFFFC0`, then `addiu 0x40`, then `movz`
 * (`if (rem) masked += 0x40;`), i.e. the if-converted form below. `a2` keeps
 * its own register (the `and`/`movz` write $a2 in place).
 * MATCH GUESS: cc=29
 */
typedef struct {
    int w0;
    int w1;
    int w2;
    int w3;
} Block16;

int FlushCache(int x);
int sceSifSetDma(Block16 *args, int x);

int sceNetcnfifSendIOP(int a0, int a1, unsigned int a2) {
    Block16 args;

    if ((a2 & 0x3F) != 0)
        a2 = (a2 & 0xFFFFFFC0) + 0x40;
    else
        a2 = a2 & 0xFFFFFFC0;
    args.w0 = a0;
    args.w1 = a1;
    args.w2 = a2;
    args.w3 = 0;
    FlushCache(0);
    return sceSifSetDma(&args, 1);
}
