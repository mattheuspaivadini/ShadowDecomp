/* STATUS (Session 7, 2026-10-14): NON_MATCHING. best score 2 [cc=29, default, variant best_intret].
 * twin of 022BD8 (command 8); residual: $s0/$s1 role swap.
 * The original .s stays in the build (asm/cod/022C30.s); this C
 * draft (Session 7) is kept for the record. */
/* v10: mirror the matched 022DA0 (int wrapper, `return` the command call). */
int func_001221D0(void);
void func_00128FB0(char *dst, char *src);
int func_00123260(char *dst, char *src, int n);

extern char D_00167F00[];
extern char D_00167EC0[];

int func_00122C30(int a0) {
    func_001221D0();
    func_00128FB0(D_00167F00 + 0x10, (char *)a0);
    return func_00123260(D_00167EC0, D_00167F00, 8);
}
