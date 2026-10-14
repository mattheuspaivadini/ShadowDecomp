/* STATUS (Session 7, 2026-10-14): NON_MATCHING. best score 3 [cc=29, default].
 * func_001230B0 + 9-arg func_00109980 (cmd 0xF); slt/movn select differs.
 * The original .s stays in the build (asm/cod/0222D8.s); this C
 * draft (subagent-produced, Session 7) is kept for the record. */
/* asm/cod/0222D8.s -> func_001222D8 @ 0x001222D8 (0x60 bytes, 24 insns)
 *
 * D_00167F00 transfer with command 0xF (the 0221xx/0222xx command family):
 *
 *   func_001230B0(a0);              ; framed init/deinit triple around
 *                                   ; D_00169F10/D_00169F58 (src/non_matching/
 *                                   ; 0230B0.c); $a0 is forwarded untouched
 *   func_001221D0();                ; id + clear the D_00167F00 block
 *   r = func_00109980(&D_00167EC0, 0xF, 0, &D_00167F00, 0x1000,
 *                     &D_00167F00, 0x1000, 0, 0);
 *   if (r >= 0) r = 0;              ; slt (-1 < r) then movn $v0,$zero
 *   return r;
 *
 * The 9-argument call is the matched 015A30.c shape (9th argument = the
 * `sw $zero,0x0($sp)` stack word, and $a5 is re-materialised from the register
 * holding &D_00167F00, here $a3). func_001222D8's own parameter count is
 * UNCONFIRMED (the bytes cannot distinguish `func_001230B0(a0)` from an
 * unprototyped `func_001230B0()`); only $a0 has to be live at the call.
 * MATCH GUESS: cc=29 (the 0221xx/0222xx family is cc=29 throughout, e.g. the
 * matched 0221D0.c; 16-byte-spaced $ra/$s0 frame) */
int func_001230B0(int a0);
int func_001221D0(void);
int func_00109980(int a0, int a1, int a2, int a3, int a4, int a5, int a6,
                  int a7, int a8);

extern char D_00167EC0[];   /* .bss 0x00167EC0, 0x40 bytes */
extern char D_00167F00[];   /* .bss 0x00167F00, 0x1000 bytes */

int func_001222D8(int a0) {
    int r;

    func_001230B0(a0);
    func_001221D0();
    r = func_00109980((int)D_00167EC0, 0xF, 0, (int)D_00167F00, 0x1000,
                      (int)D_00167F00, 0x1000, 0, 0);
    if (r >= 0)
        r = 0;
    return r;
}
