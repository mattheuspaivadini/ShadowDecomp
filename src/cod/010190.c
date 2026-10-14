/* asm/cod/010190.s -> func_00110190 @ 0x00110190 (0x48 bytes, 18 insns)
 *   r = func_00110000(a0, a1, a2);         (loader/pack helper, returns a ptr)
 *   func_00110118();                       (tail-calls func_0010F550)
 *   func_00106C20(r, a1, D_001326B0 + 4);  (syscall 6, tail call)
 * $s1 keeps a1 across both calls, $s0 keeps the first result; the frame is
 * torn down before the `j` (the syscall's value is what the caller sees).
 * MATCH GUESS: cc=29 (0x010118/0x0104xx are 2.9 tail-call shapes) */
extern int func_00110000(int a0, int a1, int a2);
extern void func_00110118(void);
extern void func_00106C20(int a0, int a1, int a2);
extern int D_001326B0[];   /* .data 0x001326B0: lui/%lo (non-small) */

void func_00110190(int a0, int a1, int a2) {
    int r;

    r = func_00110000(a0, a1, a2);
    func_00110118();
    func_00106C20(r, a1, D_001326B0[0] + 4);
}
