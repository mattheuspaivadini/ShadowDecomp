/* STATUS (Session 10b, 2026-10-15): NON_MATCHING. best score 3 [cc=29].
 * register allocation: orig lui v1/lw v0 for D_00135958, ours swaps v0/v1; 17 diff-driven variants (store order, temps, volatile, struct, const-local base) all 3. Log build/s10/notes_10b.md
 * The original .s stays in the build (asm/cod/022550.s); this C
 * draft (Session 10b) is kept for the record. */
int func_001221D0(void);
void func_00128FB0(char *dst, char *src);
int func_00123260(char *dst, char *src, int n);
extern char D_00167F00[];
extern char D_00167EC0[];
extern int D_00135958[];

int func_00122550(int a0, int a1, int a2, int a3) {
    int lit_0 = 0x10;
    int lit_1 = 0x110;

    func_001221D0();
    func_00128FB0(D_00167F00 + lit_0, (char *)a0);
    *(int *)(D_00167F00 + 8) = a1;
    func_00128FB0(D_00167F00 + lit_1, (char *)a2);
    *(int *)(D_00167F00 + 0xC) = a3;
    *(int *)(D_00167F00 + 4) = D_00135958[0];
    return func_00123260(D_00167EC0, D_00167F00, 2);
}
