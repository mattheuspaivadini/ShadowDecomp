/* STATUS (Session 9, 2026-10-15): NON_MATCHING. best score 39 [cc=29].
 * session9 R2 waveA; residual class not auto-classified
 * The original .s stays in the build (asm/cod/008FF8.s); this C
 * draft (Session 9) is kept for the record. */
struct R08FF8 {
    int f00;    /* 0x00 */
    int f04;    /* 0x04 */
    int f08;    /* 0x08 */
    int f0C;    /* 0x0C */
    int f10;    /* 0x10 */
    int f14;    /* 0x14 */
    int f18;    /* 0x18 */
    int f1C;    /* 0x1C */
    int f20;    /* 0x20 */
    int f24;    /* 0x24 */
};

extern __attribute__((section(".data"))) int D_00132288;
extern int D_00144140[];   /* 0x800 bytes, non-small -> lui/%lo */
extern int D_00144940[];
extern int D_00145140[];
extern int D_00145940[];   /* 0x40 bytes */

extern int  func_0010FB20(void);
extern int  func_0010FB70(void);
extern void func_00112918(void);
extern void func_00112C00(int id, int handler, int data);
extern int  func_001073F0(int id);
extern void func_00112E00(int a0, int a1, int a2, int a3, int a4, int a5);
extern int  func_001128D0(int a0);
extern int  func_001073E0(int a0, int a1);
extern void func_001092F8(void);
extern void func_001096D0(void);
extern void func_001098F0(void);
extern void func_00109408(void);

int func_00108FF8(void) {
    struct R08FF8 *q;
    int base;
    int r;

    func_0010FB20();
    if (D_00132288 != 0)
        return func_0010FB70();
    D_00132288 = 1;
    func_0010FB70();
    func_00112918();
    func_0010FB20();
    base = (int)D_00144140;
    q = (struct R08FF8 *)D_00145940;
    q->f20 = 0x20;
    ((int *)D_00145940)[0] = 1;
    q->f14 = (int)D_00144940 | 0x20000000;
    q->f04 = base | 0x20000000;
    q->f1C = (int)D_00145140 | 0x20000000;
    q->f08 = 0x20;
    q->f0C = 0;
    q->f10 = 0;
    q->f18 = 0x20;
    q->f24 = 0;
    func_00112C00(0x80000008, (int)func_001092F8, (int)q);
    func_00112C00(0x80000009, (int)func_001096D0, (int)q);
    func_00112C00(0x8000000A, (int)func_001098F0, (int)q);
    func_00112C00(0x8000000C, (int)func_00109408, (int)q);
    func_0010FB70();
    r = func_001073F0(0x80000002);
    if (r != 0)
        return r;
    *(int *)((char *)D_00144140 + 0x4C) = 1;
    func_00112E00(0x80000002, (int)((char *)D_00144140 + 0x40), 0x10, 0, 0, 0);
    while (func_001128D0(0) == 0)
        ;
    return func_001073E0(0x80000002, 1);
}
