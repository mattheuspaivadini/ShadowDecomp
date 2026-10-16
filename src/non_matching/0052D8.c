/* STATUS (Session 8, 2026-10-14): NON_MATCHING. best score 40 [cc=296].
 * R2 w45a_1: constants/block-layout (hang blocks; folded delay literal)
 * The original .s stays in the build (asm/cod/0052D8.s); this C
 * draft (Session 8) is kept for the record. */
extern int  D_0013A180;     /* .sbss blob (%gp_rel), accessed at +8 */
extern char D_0013EAC0[];   /* lui/%lo */
extern char D_00137410[];   /* lui/%lo message */
extern char D_00137428[];   /* lui/%lo message */

int  CreateSema(void *args);     /* syscall 0x40: CreateSema */
int  func_001285C0(char *fmt, ...);
int  sceSifInitRpc(int a0);
int  sceSifBindRpc(int a0, int a1, int a2);

int usbSerialSysInit(void) {
    int buf[8];
    int h;
    int r;
    int v;
    char *p;

    buf[1] = 1;
    buf[2] = 1;
    h = CreateSema(buf);
    *(int *)((char *)&D_0013A180 + 8) = h;
    if (h == -1) {
        func_001285C0(D_00137410);
        for (;;) {
            __asm__ __volatile__("nop\n\tnop\n\tnop\n\tnop\n\tnop");
        }
    }
    sceSifInitRpc(0);
    p = D_0013EAC0;
    for (;;) {
        r = sceSifBindRpc((int)p, 0x80000220, 0);
        if (r < 0) {
            func_001285C0(D_00137428);
            for (;;) {
                __asm__ __volatile__("nop\n\tnop\n\tnop\n\tnop\n\tnop");
            }
        }
        if (*(int *)(p + 0x24) != 0)
            break;
        v = 0xFFFF;
        v -= 4;
        for (;;) {
            __asm__ __volatile__("nop\n\tnop\n\tnop\n\tnop\n\tnop");
            if (v == -1)
                break;
            v -= 4;
        }
    }
    return 0;
}
