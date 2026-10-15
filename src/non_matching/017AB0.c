/* STATUS (Session 8, 2026-10-14): NON_MATCHING. best score 129 [cc=29].
 * R3 famD: mode select + movn if-conversion
 * The original .s stays in the build (asm/cod/017AB0.s); this C
 * draft (Session 8) is kept for the record. */
int func_00117838(int a0);
void func_00108FF8(int a0);
int func_001097A0(int a0, int a1, int a2);
int func_00108EF8(const char *msg);
int func_00112FC8(int a0, int a1);
int func_00109980(int a0, int a1, int a2, int a3, int a4, int a5, int a6,
                  int a7, int a8);
void func_00116FB0(void);
void func_00117210(void);
void func_00117098(void);

extern int D_00133A50[];    /* lui/%lo (non-small) */
extern int D_00133A64[];    /* lui/%lo */
extern int D_00133A88[];    /* lui/%lo */
extern int D_00133A8C[];    /* lui/%lo */
extern int D_00133A7C[];    /* lui/%lo */
extern int D_00133A94[];    /* lui/%lo */
extern int D_00133A90[];    /* lui/%lo */
extern int D_00133A78[];    /* lui/%lo */
extern int D_00133A9C[];    /* lui/%lo */
extern int D_00133A98[];    /* lui/%lo */
extern int D_00133A68[];    /* lui/%lo */
extern int D_00133A6C[];    /* lui/%lo */
extern int D_00133A60[];    /* lui/%lo */
extern int D_00133A84[];    /* lui/%lo */
extern char D_00138A00[];   /* lui/addiu */
extern char D_00138A20[];   /* lui/addiu */
extern char D_00151028[];   /* lui/addiu, command object */
extern char D_00151080[];   /* lui/addiu, request block */
extern char D_00134C40[];   /* lui/addiu, reply block   */

int func_00117AB0(int a0) {
    int i;
    int s0;
    int mode;
    int w4;
    int w8;

    if (func_00117838(1) != 0)
        return 0;
    func_00108FF8(0);
    D_00133A64[0] = 1;
    D_00133A88[0] = -1;
    D_00133A8C[0] = -1;
    D_00133A7C[0] = -1;
    D_00133A94[0] = -1;
    D_00133A90[0] = -1;
    D_00133A78[0] = 0;
    D_00133A9C[0] = D_00133A9C[0] + 1;
    D_00133A98[0] = -1;
    for (;;) {
        if (func_001097A0((int)D_00151028, 0x80000592, 0) < 0) {
            if (D_00133A50[0] > 0)
                func_00108EF8(D_00138A00);
            i = 0x100000;
            while (i != -1) {
                i--;
                __asm__ __volatile__ ("nop\n\tnop\n\tnop\n\tnop");
            }
            continue;
        }
        if (D_00151028[9] != 0)
            break;
        i = 0x100000;
        while (i != -1) {
            i--;
            __asm__ __volatile__ ("nop\n\tnop\n\tnop\n\tnop");
        }
    }
    D_00151080[0] = a0;
    D_00133A98[0] = 0;
    func_00112FC8((int)D_00151080, 4);
    if (func_00109980((int)D_00151028, 0, 0, (int)D_00151080, 4,
                      (int)D_00134C40, 0x10, 0, 0) < 0) {
        D_00133A64[0] = 0;
        return 0;
    }
    mode = *(int *)((((int)D_00134C40) + 0xC) | 0x20000000);
    w4 = *(int *)((((int)D_00134C40) + 4) | 0x20000000);
    w8 = *(int *)((((int)D_00134C40) + 8) | 0x20000000);
    s0 = 1;
    if (mode == 0xFF) {
        ;
    } else if (mode == 0xFE) {
        D_00133A50[0] = 1;
    } else {
        mode = -1;
        if (((mode < w4 ? w4 : w4 + 0xFF) >> 8) < 2)
            s0 = 2;
        else if (((mode < w8 ? w8 : w8 + 0xFF) >> 8) < 2)
            s0 = 2;
    }
    D_00133A64[0] = 0;
    if (a0 == 5) {
        if (D_00133A50[0] > 0)
            func_00108EF8(D_00138A20);
        func_00117098();
        D_00133A68[0] = -1;
        D_00133A6C[0] = -1;
        D_00133A60[0] = -1;
        D_00133A84[0] = 0;
    } else {
        func_00116FB0();
        func_00117210();
        D_00133A84[0] = 1;
    }
    return s0;
}
