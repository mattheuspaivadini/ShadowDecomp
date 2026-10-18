/* asm/cod/0078F0.s -> iRotateThreadReadyQueue.
 * iRotateThreadReadyQueue; request ring as a struct (rd/wr + byte pairs), direct req[n] indexing (Session 22)
 * MATCHED. */
struct Req07 { unsigned char cmd; unsigned char arg; };
struct Queue07 {
    int rd;                     /* 0x0 */
    int wr;                     /* 0x4 */
    struct Req07 req[0x200];    /* 0x8 */
};
extern int D_00132280 __attribute__((section(".data")));
extern int D_00143C90 __attribute__((section(".data")));
extern struct Queue07 D_00143C98;

void iSignalSema(int sema);

int iRotateThreadReadyQueue(unsigned int prio) {
    int n;

    if (prio >= 0x80)
        return -1;
    if (D_00132280 == 0)
        return -1;
    n = D_00143C98.wr & 0x1FF;
    D_00143C98.wr = n + 1;
    D_00143C98.req[n].cmd = 1;
    D_00143C98.req[n].arg = prio;
    iSignalSema(D_00143C90);
    return prio;
}
