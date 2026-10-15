/* STATUS (Session 8, 2026-10-14): NON_MATCHING. best score 29 [cc=296].
 * R2 w45a_0: reg-alloc ($gp reload pair after the first call)
 * The original .s stays in the build (asm/cod/002360.s); this C
 * draft (Session 8) is kept for the record. */
extern char D_001368A0[];
extern char D_001368E0[];
extern int  D_00131D80[];

int  func_00106ED0(int a0);
void func_00102608(void);
void func_00106E70(int a0, int a1);
void func_0010FB70(void);
void func_00102CF8(int a0, int a1);
int  func_00107280(int a0);
void func_00100BF8(int a0, ...);

void func_00102360(int a0, int a1, int a2, int a3, int a4, int *a5) {
    int *q;
    int *p;
    int t;
    int i;

    t = func_00106ED0(a0);
    func_00102608();
    func_00106E70(t, 0x7F);
    func_0010FB70();
    func_00102CF8((int)D_001368A0, t);
    q = a5;
    p = D_00131D80;
    for (i = 0; i < 0x20; i++) {
        p[0] = q[0];
        q += 4;
        p[0x40] = func_00107280(i);
        p += 2;
    }
    *(int *)((char *)D_00131D80 + 0x170) = a2;
    *(int *)((char *)D_00131D80 + 0x168) = a1;
    func_00100BF8((int)D_001368E0);
}
