/* STATUS (Session 7, 2026-10-14): NON_MATCHING. best score 2 [cc=29, default].
 * one-shot CreateSema pair for D_00132320/24.
 * The original .s stays in the build (asm/cod/00A0B0.s); this C
 * draft (subagent-produced, Session 7) is kept for the record. */
/* asm/cod/00A0B0.s -> func_0010A0B0 @ 0x0010A0B0 (0x70 bytes, 28 insns)
 *
 * One-shot pair of CreateSema handles (func_00106FE0 = `addiu $v1,$zero,0x40;
 * syscall 0`) sharing one 0x20-byte stack parameter block (the matched 00FB88
 * layout, option pointer in field 0x14):
 *   if (D_00132320 != -1) return;        ; bne v0,-1 -> epilogue
 *   buf.f04 = 1;
 *   buf.f14 = (int)D_00137EE0;
 *   buf.f08 = 1;                         ; sw $v1,0x8($sp), in the jal delay
 *   D_00132320 = func_00106FE0(&buf);
 *   buf.f14 = (int)D_00137EF0;           ; sw $v1,0x14($sp), in the jal delay
 *   D_00132324 = func_00106FE0(&buf);
 * The frame is 0x40 with buf[8] at $sp+0, $s0 at 0x20 and $ra at 0x30; $s0
 * holds the lui half of D_00132320 across the first call, and the -1 guard is
 * `addiu $v1,$zero,-1` (a signed literal).
 * MATCH GUESS: cc=29 (00FB88 / 0231A8 CreateSema family; 00A798 in this block
 * is cc=29)
 */
struct S00A0B0 {
    int   f00;      /* 0x00 */
    int   f04;      /* 0x04 */
    int   f08;      /* 0x08 */
    int   f0C;      /* 0x0C */
    int   f10;      /* 0x10 */
    void *f14;      /* 0x14 */
    char  pad18[8]; /* 0x18 */
};

extern int D_00132320 __attribute__((section(".data")));
extern int D_00132324 __attribute__((section(".data")));
extern int D_00137EE0[];   /* the semaphore option tables (lui/%lo) */
extern int D_00137EF0[];
int func_00106FE0(void *args);

void func_0010A0B0(void) {
    struct S00A0B0 buf;

    if (D_00132320 != -1)
        return;
    buf.f04 = 1;
    buf.f14 = D_00137EE0;
    buf.f08 = 1;
    D_00132320 = func_00106FE0(&buf);
    buf.f14 = D_00137EF0;
    D_00132324 = func_00106FE0(&buf);
}
