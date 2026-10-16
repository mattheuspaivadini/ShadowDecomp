/* STATUS (Session 9, 2026-10-15): NON_MATCHING. best score 17 [cc=29].
 * session9 R2 waveA; residual class not auto-classified
 * The original .s stays in the build (asm/cod/0198B8.s); this C
 * draft (Session 9) is kept for the record. */
extern __attribute__((section(".data"))) int D_00135618;   /* .data 0x00135618 */
extern int D_001518C0[];
extern int D_001510C0[];

int  DIntr(void);
void EIntr(void);
void sceSifAddCmdHandler(int id, int handler, int arg);
int  sceSifSendCmd(int a0, int a1, int a2, int a3, int a4, int a5);
int  sceSifGetSreg(int a0);
int  sceSifAddRebootNotifyHandler(int a0, int a1, int a2);
void func_00119AC0(void);
void func_001199A0(int a0);

int sceSifMInitRpc(void) {
    int r;
    int *p;

    if (D_00135618 != 0)
        return D_00135618;
    D_00135618 = 1;
    DIntr();
    D_001518C0[2] = 0x20;
    D_001518C0[0] = 1;
    D_001518C0[1] = (int)D_001510C0 | 0x20000000;
    D_001518C0[3] = 0;
    D_001518C0[4] = 0;
    sceSifAddCmdHandler(0x80000018, (int)func_00119AC0, (int)D_001518C0);
    EIntr();
    p = (int *)((int)D_001510C0 + 0x40);
    p[5] = 1;
    p[4] = 1;
    sceSifSendCmd(0x80000001, (int)p, 0x18, 0, 0, 0);
    do {
        r = sceSifGetSreg(1);
    } while (r == 0);
    return sceSifAddRebootNotifyHandler(0x80000014, (int)func_001199A0, 0);
}
