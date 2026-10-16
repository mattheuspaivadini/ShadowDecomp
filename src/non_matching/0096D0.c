/* STATUS (Session 8, 2026-10-14): NON_MATCHING. best score 22 [cc=29].
 * R2 w45a_2: clean guess but not byte-exact
 * The original .s stays in the build (asm/cod/0096D0.s); this C
 * draft (Session 8) is kept for the record. */
extern int func_00109288(int a0);
extern int func_00109640(int key, int n);
extern int isceSifSendCmd(int cmd, void *p, int size, int a, int b, int c);
extern int iSetTimerAlarm(int a0, void (*a1)(), void *a2);
extern int func_00109690(int a0, int a1, int a2, char *p);

int func_001096D0(int a0, int a1) {
    int *p = (int *)a0;
    int *q;
    int e;
    int r;

    q = (int *)func_00109288(a1);
    q[7] = p[7];
    q[5] = p[5];
    q[8] = 0x80000009;
    e = func_00109640(p[8], a1);
    if (e != 0) {
        q[9] = e;
        q[10] = *(int *)(e + 8);
    } else {
        q[9] = 0;
        q[10] = 0;
    }
    r = isceSifSendCmd(0x80000008, q, 0x40, 0, 0, 0);
    if (r != 0)
        return r;
    return iSetTimerAlarm(0x800, func_00109690, q);
}
