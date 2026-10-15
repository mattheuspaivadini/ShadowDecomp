/* asm/cod/017700.s -> SceSifrpcCall.
 * 9-arg cmd 0xE + uncached mirror read; famA (R3)
 * MATCHED (Session 8). */
extern char D_00134C10[];   /* request struct -> lui/%lo */
extern char D_00133AC0[];   /* 4-byte reply buffer -> lui/%lo */
extern int D_00133A68[];    /* handle word -> lui/%lo */

int SceSifrpcCall(int a0, int a1, int a2, int a3, int a4, int a5, int a6,
                  int a7, int a8);
int func_001175A8(int a0);
int func_00107000(int a0);

int func_00117700(void) {
    int r;

    if (func_001175A8(2) == 0)
        return 0;
    r = SceSifrpcCall((int)D_00134C10, 0xE, 0, 0, 0, (int)D_00133AC0, 4, 0, 0);
    if (r < 0) {
        func_00107000(D_00133A68[0]);
        return 0;
    }
    r = *(int *)((unsigned int)D_00133AC0 | 0x20000000);
    func_00107000(D_00133A68[0]);
    return r;
}
