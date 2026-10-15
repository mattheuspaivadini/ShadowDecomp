/* STATUS (Session 8, 2026-10-14): NON_MATCHING. best score 33 [cc=29].
 * R2 w45a_2: rotated-loop (n++ before the while; 0x100000 delay loop)
 * The original .s stays in the build (asm/cod/00DEF8.s); this C
 * draft (Session 8) is kept for the record. */
extern int D_0013232C __attribute__((section(".data")));
extern unsigned char D_00147280[];
extern int D_001471C0[];
extern int D_00147200[];

int SceSifrpcCall(int a0, int a1, int a2, int a3, int a4, int a5, int a6,
                  int a7, int a8);

int func_0010DEF8(unsigned char *a0, int a1) {
    unsigned char c;
    int n;
    int r;

    if (D_0013232C < 0)
        return 0;
    c = a0[0];
    D_00147280[4] = c;
    n = 0;
    if (c != 0) {
        n++;
        while (n < 0xFC) {
            c = a0[n];
            D_00147280[n + 4] = c;
            n++;
            if (c == 0)
                break;
        }
    }
    if (n == 0xFC) {
        n = 0xFB;
        D_00147280[0xFF] = 0;
        *(int *)D_00147280 = a1;
    } else {
        *(int *)D_00147280 = a1;
    }
    D_00147280[0xFF] = 0;
    r = SceSifrpcCall((int)D_001471C0, 3, 0, (int)D_00147280, n + 5,
                      (int)D_00147200, 4, 0, 0);
    if (r < 0)
        return -1;
    return D_00147200[0];
}
