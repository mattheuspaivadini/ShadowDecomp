/* STATUS (Session 19, 2026-10-17): NON_MATCHING. best score 6 [cc=29].
 * request record as struct via a kept pointer (s1); residual = schedule of the first copy load/store pair
 * The original .s stays in the build (asm/cod/015E40.s); this C
 * draft (Session 19) is kept for the record. */
int sceSifCallRpc(int a0, int a1, int a2, int a3, int a4, int a5, int a6,
                  int a7, int a8);
int WaitSema(int a0);
int SignalSema(int a0);
void func_00116C58(int a0, ...);

struct dbc_sock {
    int  f00;
    int  f04;
    int  f08;
    int  f0C;
    int  f10;
    char name[16];      /* 0x14 */
};

struct dbc_req {
    int  f00;
    int  f04;
    int  f08;
    int  f0C;
    int  f10;
    char name[16];      /* 0x14 */
    int  result;        /* 0x24 */
    int  f28;
    int  f2C;
};

extern int D_0014E900[];    /* .bss 0x0014E900, lui/%lo */
extern int D_0014EA00[];    /* .bss 0x0014EA00, lui/%lo */
extern int D_00150DC0[];    /* lui/%lo: the DBC lock word */
extern int D_00133A28[];    /* lui/%lo: the module-ready flag */
extern char D_00138680[];   /* lui/%lo: the error message */

int sceDbcCreateSocket(struct dbc_sock *s, int a1, int a2) {
    struct dbc_req *q;
    int i;
    int r;

    if (D_00133A28[0] == 0)
        return 0;
    WaitSema(D_00150DC0[0]);
    q = (struct dbc_req *)D_0014EA00;
    q->f00 = s->f00;
    q->f28 = a1;
    q->f2C = a2;
    q->f04 = s->f04;
    q->f08 = s->f08;
    q->f0C = s->f0C;
    q->f10 = s->f10;
    for (i = 0; i < 0x10; i++)
        q->name[i] = s->name[i];
    if (sceSifCallRpc((int)D_0014E900, 0x80001301, 0, (int)D_0014EA00, 0x90,
                      (int)D_0014EA00, 0x90, 0, 0) < 0) {
        func_00116C58((int)D_00138680);
        SignalSema(D_00150DC0[0]);
        return 0;
    }
    r = q->result;
    SignalSema(D_00150DC0[0]);
    return r;
}
