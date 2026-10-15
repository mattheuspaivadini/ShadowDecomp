/* STATUS (Session 9, 2026-10-15): NON_MATCHING. best score 42 [cc=29].
 * session9 R1; residual class not auto-classified
 * The original .s stays in the build (asm/cod/022128.s); this C
 * draft (Session 9) is kept for the record. */
int func_001097A0(int a0, int a1, int a2);
int func_00109B80(int a0);
extern int D_0013595C[];
extern char D_00167EC0[];

int func_00122128(void) {
    int i;

    if (D_0013595C[0] != 0)
        return 0;
    for (;;) {
        if (func_001097A0((int)D_00167EC0, 0x80001101, 1) < 0)
            return -1;
        while (func_00109B80((int)D_00167EC0) != 0)
            ;
        if (*(int *)(D_00167EC0 + 0x24) != 0) {
            D_0013595C[0] = 1;
            return 0;
        }
        for (i = 0xFFFF; i != -1; i--)
            ;
    }
}
