/* asm/cod/010200.s -> func_00110200 @ 0x00110200 (0x4C bytes, 19 insns)
 *   func_00110000(&D_00138270, a0, a1);   (8-byte .rodata object as the source)
 *   func_00110118();                      (tail-calls func_0010F550)
 *   func_00107400(a0, D_001326B0 + 4);    (syscall 0x7B, tail call)
 * $s0 keeps a0 (used by the last call); D_001326B0 is reloaded after the second
 * call and `+ 4` is added in the same `addiu a1, a1, 4`.
 * MATCH GUESS: cc=29 (0x010118/0x0104xx are 2.9 tail-call shapes) */
extern int func_00110000(int *p, int a0, int a1);
extern void func_00110118(void);
extern void func_00107400(int a0, int a1);
extern int D_00138270[];   /* .rodata 0x00138270: 2 words, address taken */
extern int D_001326B0[];   /* .data   0x001326B0 (non-small) */

void func_00110200(int a0, int a1) {
    func_00110000(D_00138270, a0, a1);
    func_00110118();
    func_00107400(a0, D_001326B0[0] + 4);
}
