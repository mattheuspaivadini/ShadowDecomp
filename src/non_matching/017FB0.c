/* STATUS (Session 8, 2026-10-14): NON_MATCHING. best score 53 [cc=29].
 * R3 famD: retry counter with 0x11 timeout
 * The original .s stays in the build (asm/cod/017FB0.s); this C
 * draft (Session 8) is kept for the record. */
int func_00108EF8(const char *msg);
void func_00116FB0(void);
int func_00107030(int a0);
void func_00107000(int a0);
void func_00108FF8(int a0);
int func_0010FB20(void);
void func_0010FB70(void);
int func_001097A0(int a0, int a1, int a2);
int func_00112FC8(int a0, int a1);
int func_00109980(int a0, int a1, int a2, int a3, int a4, int a5, int a6,
                  int a7, int a8);
int func_00117D98(int a0);

extern int D_00133A50[];    /* lui/%lo (non-small) */
extern int D_00133A80[];    /* lui/%lo */
extern int D_00133A70[];    /* lui/%lo */
extern int D_00133A90[];    /* lui/%lo */
extern char D_00138A80[];   /* lui/addiu */
extern char D_00138A48[];   /* lui/addiu */
extern char D_00138A68[];   /* lui/addiu */
extern char D_00151050[];   /* lui/addiu, command object */
extern char D_00151090[];   /* lui/addiu, request block */
extern char D_001354C0[];   /* lui/addiu, reply block   */

int func_00117FB0(int a0) {
    int i;
    int s1;
    int r;

    if (D_00133A50[0] > 0)
        func_00108EF8(D_00138A80);
    func_00116FB0();
    if (D_00133A70[0] != func_00107030(D_00133A70[0]))
        return (a0 == 8) ? -1 : 6;
    func_00108FF8(0);
    if (D_00133A90[0] < 0) {
        s1 = 0;
        for (;;) {
            if (func_001097A0((int)D_00151050, 0x8000059C, 0) < 0) {
                if (D_00133A50[0] > 0)
                    func_00108EF8(D_00138A48);
                i = 0x100000;
                while (i != -1) {
                    i--;
                    __asm__ __volatile__ ("nop\n\tnop\n\tnop\n\tnop");
                }
                continue;
            }
            if (D_00151050[9] != 0) {
                D_00133A90[0] = 0;
                break;
            }
            if (s1++ >= 0x11) {
                func_00107000(D_00133A70[0]);
                return func_00117D98(a0);
            }
            i = 0x100000;
            while (i != -1) {
                i--;
                __asm__ __volatile__ ("nop\n\tnop\n\tnop\n\tnop");
            }
        }
    }
    r = func_0010FB20();
    D_00133A80[0] = 0;
    if (r != 0)
        func_0010FB70();
    D_00151090[0] = a0;
    func_00112FC8((int)D_00151090, 4);
    if (func_00109980((int)D_00151050, 0, 0, (int)D_00151090, 4,
                      (int)D_001354C0, 4, 0, 0) < 0) {
        func_00107000(D_00133A70[0]);
        return (a0 == 8) ? -1 : 6;
    }
    if (D_00133A50[0] > 0)
        func_00108EF8(D_00138A68);
    r = *(int *)(((int)D_001354C0) | 0x20000000);
    func_00107000(D_00133A70[0]);
    return r;
}
