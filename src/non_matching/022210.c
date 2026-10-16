/* STATUS (Session 11a, 2026-10-15): NON_MATCHING. best score 2 [cc=29].
 * Session 11a R1-R3: 8 variants (ifelse, reversed, void proto, temps, pre-saved
 * locals, comma-return, asm barrier). Residual: the error-path call's two
 * register copies are ordered [a1=s2][a0=s1] in the original but forward
 * [a0=s1][a1=s2] by every published EE-GCC (probe2/3/5, notes_11a.md);
 * only those 2 words differ.
 * The original .s stays in the build (asm/cod/022210.s); this C
 * draft (Session 8) is kept for the record. */
int SceSifrpcCall(int a0, int a1, int a2, int a3, int a4, int a5, int a6,
                  int a7, int a8);
int func_00123000(int a0, int a1, int a2, int a3);
int func_001221D0(void);
int func_001230B0(int a0, int a1);
int func_00106E70(int a0);

extern int D_00167EC0[];    /* .bss 0x00167EC0, 0x40 bytes, lui/%lo */
extern int D_00167F00[];    /* .bss 0x00167F00, 0x1000 bytes, lui/%lo */

int func_00122210(int *a0, int a1, int a2, int a3) {
    int h;
    int r;

    if (a0 == 0)
        return -0x65;
    h = func_00123000((int)a0, a1, a2, 1);
    if (h < 0)
        return -1;
    func_001221D0();
    D_00167F00[2] = *a0;
    r = SceSifrpcCall((int)D_00167EC0, 0xB, 0, (int)D_00167F00, 0x1000,
                      (int)D_00167F00, 0x1000, 0, 0);
    if (r < 0) {
        func_001230B0(h, a3);
        return r;
    }
    func_00106E70(h);
    return h;
}
