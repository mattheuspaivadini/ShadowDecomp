/* asm/cod/022E68.s -> func_00122E68 @ 0x00122E68 (0x3C bytes, 15 insns)
 * Loader-style init/teardown pair: r = func_00122DE0() (which runs the
 * func_00123260(...,0x66) table init); func_001232F0(0) (the matching
 * de-init); then D_0013595C = 0 and `return r`.  The store is the last
 * statement before the return, which is why its `lui`/`sw` land after the
 * epilogue's `ld`s, and `r` is copied to $v0 (`daddu $v0,$s0,$zero`) - not a
 * tail call (the returned value is the saved first call).
 * MATCH GUESS: cc=296 (0x122D6x/0x122DEx family is 2.96 + no-sibling-calls) */
extern int func_00122DE0(void);
extern void func_001232F0(int a0);
extern int D_0013595C[];   /* .data 0x0013595C: lui/%lo (non-small) */

int func_00122E68(void) {
    int r;

    r = func_00122DE0();
    func_001232F0(0);
    D_0013595C[0] = 0;
    return r;
}
