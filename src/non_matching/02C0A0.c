/* STATUS (Session 7, 2026-10-14): NON_MATCHING. best score 11 [cc=296, default].
 * print-context variant with FILE/buffer args.
 * The original .s stays in the build (asm/cod/02C0A0.s); this C
 * draft (subagent-produced, Session 7) is kept for the record. */
/* asm/cod/02C0A0.s -> func_0012C0A0 @ 0x0012C0A0 (0x54 bytes, 21 insns)
 *
 * Print-context wrapper with an explicit FILE: same 0x60-byte context block as
 * func_0012C048, but the FILE field (0x54) comes from the first argument and the
 * buffer pointers (0x00/0x10) from the second; the third and fourth arguments
 * are forwarded to func_00129930 as its 2nd/3rd argument (the first argument is
 * thus shifted into $a1):
 *   a4 = a1 (buf); a1 = a2 (fmt); a2 = a3 (ap);
 *   ctx.f54 = file; ctx.f14 = ctx.f08 = 0x7FFFFFFF; ctx.f0C = 0x208;
 *   ctx.p10 = buf; ctx.p00 = buf;
 *   func_00129930(&ctx, fmt, ap);
 *   *ctx.p00 = 0;                 (lw $v1,0x0($sp); sb $zero,0x0($v1))
 * Store order: 0x54, 0x14, 0x08, 0x0C, 0x10, 0x00 (the last in the jal delay
 * slot). Frame 0x70 with $ra at 0x60.
 * MATCH GUESS: cc=296 */
struct S12C0A0 {
    char *p00;          /* 0x00 the output buffer */
    int   pad04;        /* 0x04 */
    int   f08;          /* 0x08 0x7FFFFFFF    */
    short f0C;          /* 0x0C 0x208         */
    char  pad0E[2];
    char *p10;          /* 0x10 the output buffer again */
    int   f14;          /* 0x14 0x7FFFFFFF    */
    char  pad18[0x3C];  /* 0x18..0x53         */
    int   f54;          /* 0x54 the FILE argument */
    char  pad58[4];     /* 0x58..0x5B (locals end 0x5C -> $ra at 0x60) */
};

int func_00129930(void *ctx, ...);

void func_0012C0A0(int file, char *buf, char *fmt, int ap) {
    struct S12C0A0 ctx;

    ctx.f54 = file;
    ctx.f14 = 0x7FFFFFFF;
    ctx.f08 = 0x7FFFFFFF;
    ctx.f0C = 0x208;
    ctx.p10 = buf;
    ctx.p00 = buf;
    func_00129930(&ctx, fmt, ap);
    *ctx.p00 = 0;
}
