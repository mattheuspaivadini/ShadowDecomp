/* STATUS (Session 8, 2026-10-14): NON_MATCHING. best score 12 [cc=296].
 * R2 w45a_0: dead 0xFF804000 as func_00105990's $a0
 * The original .s stays in the build (asm/cod/001CC8.s); this C
 * draft (Session 8) is kept for the record. */
extern int  D_00139E00;     /* .sdata, right below D_00139E04 */
extern int  D_00139E04;
extern int  D_00131C44[];   /* .data slot, absolute address */
extern char D_00131BAC[];
extern char D_001363D0[];
extern char D_00136508[];

int  func_00106ED0(int a0);
int  func_00100D48(int a0);
void func_00107260(int a0);
void func_00102CF8(int a0, int a1, int a2);
void func_00105990(int a0, int a1, int a2);
int  func_001028F0(int a0);
int  func_00106E20(void);

int func_00101CC8(int a0) {
    int t;
    int r;
    int fn;

    t = func_00106ED0(a0);
    r = func_00100D48(a0);
    if (r != 0) {
        D_00131C44[0] = r;
        D_00139E00 = D_00139E04;
        fn = *(int *)(r + 0x10);
        func_00107260(0);
        func_00107260(2);
        func_00102CF8((int)D_001363D0, fn, (int)D_00131BAC);
        ((int (*)(int, int))fn)(1, (int)D_00131BAC);
    } else {
        func_00105990(0xFF804000, (int)D_00136508, r);
    }
    func_001028F0(t);
    return func_00106E20();
}
