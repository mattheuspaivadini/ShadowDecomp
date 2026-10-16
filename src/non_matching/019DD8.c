/* STATUS (Session 9, 2026-10-15): NON_MATCHING. best score 16 [cc=29].
 * session9 R2 waveA; residual class not auto-classified
 * The original .s stays in the build (asm/cod/019DD8.s); this C
 * draft (Session 9) is kept for the record. */
struct S19DD8_SEMA {           /* CreateSema parameter block (0x20 bytes) */
    char pad00[4];
    int  f04;                  /* 0x04 */
    int  f08;                  /* 0x08 */
    char pad0C[8];
    int  f14;                  /* 0x14 option table */
};

struct S19DD8_REC {            /* the 0x40 record func_001199F8 returns */
    char pad00[0x14];
    int  f14;                  /* 0x14 */
    int  f18;                  /* 0x18 */
    int  f1C;                  /* 0x1C */
    int  f20;                  /* 0x20 */
    int  f24;                  /* 0x24 */
};

struct S19DD8_A {              /* a0, the caller's state object */
    int  f00;                  /* 0x00 */
    int  f04;                  /* 0x04 */
    int  f08;                  /* 0x08 */
    char pad0C[4];
    int  f10;                  /* 0x10 */
    char pad14[0x10];
    int  f24;                  /* 0x24 */
    int  f28;                  /* 0x28 */
    int  f2C;                  /* 0x2C */
};

extern char D_00138B28[];      /* .rodata: the "SceMrpcUnbind" name */
extern int  D_00138B70[];      /* .rodata: the semaphore option table */
extern char D_001518C0[];      /* allocator state (passed by address) */

void scePrintf(char *name, int arg);
int  WaitSema(int sema);
int  SignalSema(int sema);
void *func_001199F8(void *state);
int  CreateSema(void *param);
void func_00119AA0(void *rec);
int  DeleteSema(int sema);
int  sceSifSendCmd(int cmd, int arg, int size, int a3, int a4, int a5);

int sceSifMUnBindRpc(struct S19DD8_A *s1, int a1) {
    struct S19DD8_REC  *s0;
    struct S19DD8_SEMA  sema;
    int t;
    int s2;

    if (a1 != 0) {
        scePrintf(D_00138B28, a1);
        return -1;
    }
    WaitSema(s1->f28);
    s0 = func_001199F8(D_001518C0);
    if (s0 == 0)
        return -1;
    t = s0->f18;
    s1->f00 = (int)s0;
    s1->f04 = t;
    s0->f14 = (int)s0;
    s0->f1C = (int)s1;
    s0->f20 = s1->f10;
    s0->f24 = s1->f24;
    sema.f14 = (int)D_00138B70;
    sema.f08 = 0;
    sema.f04 = 1;
    s1->f08 = CreateSema(&sema);
    s2 = s1->f08;
    if (s2 < 0) {
        func_00119AA0(s0);
        return -3;
    }
    if (sceSifSendCmd(0x8000001D, (int)s0, 0x40, 0, 0, 0) == 0) {
        func_00119AA0(s0);
        DeleteSema(s2);
        return -2;
    }
    WaitSema(s2);
    DeleteSema(s2);
    if (s1->f2C == 1)
        DeleteSema(s1->f28);
    return s1->f2C;
}
