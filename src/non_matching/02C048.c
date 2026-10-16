/* STATUS (10, 2026-10-16): NON_MATCHING. best score 7 [cc=296].
 * 
 * The original .s stays in the build (asm/cod/02C048.s); this C
 * draft (10) is kept for the record. */
/* asm/cod/02C048.s -> func_0012C048 @ 0x0012C048 (0x54 bytes, 21 insns)
 *
 * Print-context wrapper: build the 0x58+/0x60-byte "print context" block on the
 * stack (buffer pointers 0x00/0x10, limits 0x7FFFFFFF at 0x08/0x14, the 16-bit
 * 0x208 field at 0x0C, the FILE at 0x54 - the default D_00135C60[0]), pass the
 * incoming second argument (the format) through to func_00129930 and then
 * NUL-terminate the buffer through the pointer field, which is re-loaded after
 * the call because the block's address escaped:
 *   ctx.p00 = buf; ctx.p10 = buf; ctx.f08 = ctx.f14 = 0x7FFFFFFF;
 *   ctx.f0C = 0x208; ctx.f54 = D_00135C60[0];
 *   func_00129930(&ctx, fmt);
 *   *ctx.p00 = 0;                 (lw $v1,0x0($sp); sb $zero,0x0($v1))
 * The store order emitted is 0x14, 0x08, 0x0C, 0x10, 0x54 and 0x00 (the last in
 * the jal delay slot); the frame is 0x70 with $ra at 0x60. func_00129930 is
 * variadic (its 3rd/4th argument registers are not set here).
 * MATCH GUESS: cc=296 (the 0x2C2xx framed trampolines in this region are 296) */
struct S12C048 {
    char *p00;          /* 0x00 the output buffer */
    int   pad04;        /* 0x04 */
    int   f08;          /* 0x08 0x7FFFFFFF    */
    short f0C;          /* 0x0C 0x208         */
    char  pad0E[2];
    char *p10;          /* 0x10 the output buffer again */
    int   f14;          /* 0x14 0x7FFFFFFF    */
    char  pad18[0x3C];  /* 0x18..0x53         */
    int   f54;          /* 0x54 the FILE      */
    char  pad58[4];     /* 0x58..0x5B (locals end 0x5C -> $ra at 0x60) */
};

int _impure_ptr[];   /* .data 0x00135C60: lui/%lo (non-small) */
int func_00129930(void *ctx, ...);

void func_0012C048(char *buf, char *fmt) {
    struct S12C048 ctx;

    ctx.f14 = 0x7FFFFFFF;
    ctx.f08 = 0x7FFFFFFF;
    ctx.f0C = 0x208;
    ctx.p10 = buf;
    ctx.f54 = _impure_ptr[0];
    ctx.p00 = buf;
    func_00129930(&ctx, fmt);
    *ctx.p00 = 0;
}
