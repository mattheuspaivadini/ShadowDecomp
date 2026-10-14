/* asm/cod/016C80.s -> func_00116C80 @ 0x00116C80 (0x68 bytes, 26 insns)
 *
 * func_0010FB20-gated one-shot: install the cross-module entry `a0` together
 * with the caller's $gp (the D_00150E00/D_00150E04 pair that func_00117138
 * completes with D_00150E08/D_00150E0C/D_00150E10 - see the non-matching
 * 0171B8.c notes):
 *
 *   if (func_00117798(1) != 0) return 0;         ; bnez -> v0 = 0
 *   a = func_0010FB20();                         ; critical-section guard
 *   old = D_00150E00[0];
 *   D_00150E00[0] = a0;
 *   D_00150E04[0] = $gp;                         ; `sw $gp,%lo(...)($a0)`
 *   if (a != 0) func_0010FB70();                 ; release
 *   return old;
 *
 * RESIDUAL: the `$gp` store has no plain-C spelling (ee-gcc only emits it for
 * its own abicalls base), so it is written as a one-statement inline-asm store
 * with a memory operand, which reproduces `lui $a0,%hi(...)` +
 * `sw $gp,%lo(...)($a0)`; whether the materialisation order matches exactly is
 * left to the scoring loop.
 * MATCH GUESS: cc=29 (the func_0010FB20 wrapper family)
 */
int func_00117798(int a0);
int func_0010FB20(void);
int func_0010FB70(void);

extern int D_00150E00[];   /* .bss 0x00150E00: installed entry address */
extern int D_00150E04[];   /* .bss 0x00150E04: caller $gp value        */

int func_00116C80(int a0) {
    int a;
    int old;

    if (func_00117798(1) != 0)
        return 0;
    a = func_0010FB20();
    old = D_00150E00[0];
    D_00150E00[0] = a0;
    __asm__ __volatile__("sw $gp, %0" ::"m"(D_00150E04[0]) : "memory");
    if (a != 0)
        func_0010FB70();
    return old;
}
