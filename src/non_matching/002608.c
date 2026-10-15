/* STATUS (Session 8, 2026-10-14): NON_MATCHING. best score 21 [cc=296].
 * R2 w45a_1: rotated-loop (three 256-entry sweeps, swapped roles)
 * The original .s stays in the build (asm/cod/002608.s); this C
 * draft (Session 8) is kept for the record. */
extern int D_0013B790[];    /* lui/%lo */
extern int D_0013C790[];    /* lui/%lo */

int  func_00106ED0(void);
int  func_00106E70(int a0, int a1);
int  func_00102438(void);
int  func_00106E30(void);
int  func_00106DF0(int a0);
int  func_00102500(void);
int  func_001032F8(void);
int  func_00108FF8(int a0);
int  func_0010DCE8(void);
int  func_0010DED8(int a0);

void func_00102608(void) {
    int i;
    int v;
    int t;
    int *p;

    i = 0xFF;
    func_00106E70(func_00106ED0(), 1);
    func_00102438();
    t = func_00106ED0();
    p = D_0013B790;
    v = *p;
    while (i >= 0) {
        if (v != t && v >= 0)
            func_00106E70(v, 0x7F);
        i--;
        p++;
        v = *p;
    }
    {
        int j;
        int n;
        int *q;

        t = func_00106ED0();
        n = -1;
        q = D_0013B790;
        for (j = 0xFF; j >= 0; j--) {
            if (*q != t && *q >= 0) {
                func_00106E30();
                func_00106DF0(*q);
                *q = n;
            }
            q++;
        }
    }
    func_00102500();
    func_001032F8();
    func_00108FF8(0);
    func_0010DCE8();
    {
        int j;
        int *q;

        q = D_0013C790;
        for (j = 0xFF; j >= 0; j--) {
            if (*q != 0) {
                func_0010DED8(*q);
                *q = 0;
            }
            q++;
        }
    }
}
