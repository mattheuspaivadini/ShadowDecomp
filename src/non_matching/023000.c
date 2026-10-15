/* STATUS (Session 9, 2026-10-15): NON_MATCHING. best score 15 [cc=29].
 * session9 R1; residual class not auto-classified
 * The original .s stays in the build (asm/cod/023000.s); this C
 * draft (Session 9) is kept for the record. */
struct S23000Ctx {
    int f00;                /* 0x00 */
    int entry;              /* 0x04 - func_00122F90 */
    int f08;                /* 0x08 */
    int f0C;                /* 0x0C */
    int gp;                 /* 0x10 */
    int f14;                /* 0x14 */
    int f18;                /* 0x18 */
    int f1C;                /* 0x1C */
    int f20;                /* 0x20 - D_00138DD0 (thread argument ptr) */
    int pad[3];             /* 0x24-0x2F */
};

struct B23000 {             /* 16-byte plain-word block (ldl/ldr/sdl/sdr) */
    unsigned int w0;        /* 0x00 */
    unsigned int w4;        /* 0x04 */
    unsigned int w8;        /* 0x08 */
    unsigned int wC;        /* 0x0C */
};

int func_00106DE0(void *param);     /* syscall 0x20: CreateThread */
int func_00107AD0(int thread, int a1);
int func_00106DF0(int a0);          /* DeleteThread */
void func_00122F90(void);           /* the thread entry point */

extern char D_00138DD0[];
extern char D_00169F00[];
extern char D_00141D70[];           /* the linker's _gp value */

int func_00123000(int a0, int a1, int a2, int a3) {
    struct S23000Ctx ctx;
    int id;

    ctx.entry = (int)func_00122F90;
    ctx.f08 = a1;
    ctx.f0C = a2;
    ctx.f14 = a3;
    ctx.gp = (int)D_00141D70;
    ctx.f20 = (int)D_00138DD0;
    id = func_00106DE0(&ctx);
    if (id <= 0)
        return -1;
    *(struct B23000 *)D_00169F00 = *(struct B23000 *)a0;
    if (func_00107AD0(id, 0) >= 0)
        return id;
    func_00106DF0(id);
    return -1;
}
