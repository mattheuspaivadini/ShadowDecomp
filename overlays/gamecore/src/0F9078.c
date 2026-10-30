/* GAMECORE.XFF @ 0x0F9078 (36 B) - chkAttainExecLayout
 * Evidence: frame + `sd $ra`; `daddu $t0,$a3` forwards the 4th argument as the
 * 5th argument (EE ABI keeps args 5-8 in $t0-$t3), `$a3` is loaded with
 * `ZeroVector`, `$f12` is zeroed (0.0f tolerance), then a sibling `j` to
 * the shared checker at .text+0xF3848.
 * UNCONFIRMED: parameter meanings; the checker's signature beyond 5 args.
 */
typedef unsigned int u_long128 __attribute__((mode(TI)));

extern u_long128 ZeroVector[];
void func_0F3848(void *a, void *b, void *c, void *zero, void *d, float tol);

void chkAttainExecLayout(void *a, void *b, void *c, void *d) {
    func_0F3848(a, b, c, ZeroVector, d, 0.0f);
}
