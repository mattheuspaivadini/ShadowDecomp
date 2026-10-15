/* STATUS (Session 8, 2026-10-14): NON_MATCHING. best score 53 [cc=29].
 * R3 famD: busy-wait + retry loop (4 in-body nops)
 * The original .s stays in the build (asm/cod/017D98.s); this C
 * draft (Session 8) is kept for the record. */
int func_00108EF8(const char *msg);
int func_0010FB20(void);
void func_0010FB70(void);
void func_00116FB0(void);
int func_00107030(int a0);
void func_00107000(int a0);
int func_00117838(int a0);
int func_001097A0(int a0, int a1, int a2);
void func_00108FF8(int a0);
int func_00112FC8(int a0, int a1);
int SceSifrpcCall(int a0, int a1, int a2, int a3, int a4, int a5, int a6,
                  int a7, int a8);

extern int D_00133A50[];    /* lui/%lo (non-small) */
extern int D_00133A80[];    /* lui/%lo */
extern int D_00133A6C[];    /* lui/%lo */
extern int D_00133A90[];    /* lui/%lo */
extern char D_00138A30[];   /* lui/addiu */
extern char D_00138A48[];   /* lui/addiu */
extern char D_00138A68[];   /* lui/addiu */
extern char D_00151050[];   /* lui/addiu, command object */
extern char D_00151090[];   /* lui/addiu, request block */
extern char D_00134C40[];   /* lui/addiu, reply block   */

int func_00117D98(int a0) {
    int i;
    int r;

    if (D_00133A50[0] > 0)
        func_00108EF8(D_00138A30);
    r = func_0010FB20();
    D_00133A80[0] = 1;
    if (r != 0)
        func_0010FB70();
    func_00116FB0();
    if (D_00133A6C[0] != func_00107030(D_00133A6C[0]))
        return 6;
    if (func_00117838(1) != 0) {
        func_00107000(D_00133A6C[0]);
        return (a0 == 8) ? -1 : 6;
    }
    func_00108FF8(0);
    if (D_00133A90[0] < 0) {
        for (;;) {
            if (func_001097A0((int)D_00151050, 0x8000059A, 0) < 0) {
                if (D_00133A50[0] > 0)
                    func_00108EF8(D_00138A48);
                i = 0x100000;
                while (i != -1) {
                    i--;
                    __asm__ __volatile__ ("nop\n\tnop\n\tnop\n\tnop");
                }
                continue;
            }
            if (D_00151050[9] != 0)
                break;
            i = 0x100000;
            while (i != -1) {
                i--;
                __asm__ __volatile__ ("nop\n\tnop\n\tnop\n\tnop");
            }
        }
        D_00133A90[0] = 0;
    }
    D_00151090[0] = a0;
    func_00112FC8((int)D_00151090, 4);
    if (SceSifrpcCall((int)D_00151050, 0, 0, (int)D_00151090, 4,
                      (int)D_00134C40, 4, 0, 0) < 0) {
        func_00107000(D_00133A6C[0]);
        return (a0 == 8) ? -1 : 6;
    }
    if (D_00133A50[0] > 0)
        func_00108EF8(D_00138A68);
    r = *(int *)(((int)D_00134C40) | 0x20000000);
    func_00107000(D_00133A6C[0]);
    return r;
}
