/* asm/cod/009D28.s -> sceSifRemoveRpc.
 * SCE sifrpc unlink; search loop exits through a goto (Session 19)
 * MATCHED. */
int DIntr(void);
int EIntr(void);

int sceSifRemoveRpc(int a0, int *a1) {
    int *p;

    DIntr();
    p = (int *)a1[0x08 / 4];
    if (p == (int *)a0) {
        a1[0x08 / 4] = p[0x38 / 4];
    } else if (p != 0) {
        while (p[0x38 / 4] != a0) {
            p = (int *)p[0x38 / 4];
            if (p == 0)
                goto out;
        }
        p[0x38 / 4] = ((int *)a0)[0x38 / 4];
    }
out:
    EIntr();
    return (int)p;
}
