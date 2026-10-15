/* STATUS (Session 8, 2026-10-14): NON_MATCHING. best score 27 [cc=29].
 * R3 famB: func_001178A8 gate + mirror read
 * The original .s stays in the build (asm/cod/018288.s); this C
 * draft (Session 8) is kept for the record. */
int SceSifrpcCall(int a0, int a1, int a2, int a3, int a4, int a5, int a6,
                  int a7, int a8);
int func_001178A8(int a0);
int func_00112FC8(int a0, int a1);
int func_00107000(int a0);

extern int D_00135080[];    /* .data 0x00135080, 0x540 bytes, lui/%lo */
extern int D_00134C40[];    /* .data 0x00134C40, 0x440 bytes, lui/%lo */
extern int D_001355C0[];    /* .data 0x001355C0, 0x28 bytes, lui/%lo */
extern int D_001355E8[];    /* .data 0x001355E8 = 0x22, lui/%lo */
extern int D_001355EC[];    /* .data 0x001355EC = 4, lui/%lo */
extern int D_001355F0[];    /* .data 0x001355F0 = 4, lui/%lo */
extern int D_00133A6C[];    /* .data 0x00133A6C, lui/%lo */

int func_00118288(int a0) {
    unsigned int addr;

    if (func_001178A8(0x22) == 0)
        return 0;
    D_00135080[0] = a0;
    func_00112FC8((int)D_00135080, 4);
    if (SceSifrpcCall((int)D_001355C0, D_001355E8[0], 0, (int)D_00135080,
                      D_001355EC[0], (int)D_00134C40, D_001355F0[0], 0,
                      0) < 0) {
        func_00107000(D_00133A6C[0]);
        return 0;
    }
    addr = (unsigned int)D_00134C40 | 0x20000000;
    func_00107000(D_00133A6C[0]);
    return *(int *)addr;
}
