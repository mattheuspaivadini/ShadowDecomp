/* asm/cod/022210.s -> sceNetcnfifCreateCallbackThread.
 * SCE SDK, cc=29 (callee arity / tail-call / base pin from the image)
 * MATCHED. */
int sceSifCallRpc(int a0, int a1, int a2, int a3, int a4, int a5, int a6,
                  int a7, int a8);
int sce_create_callback_thread(int a0, int a1, int a2, int a3);
int sceNetcnfifInit(void);
void sce_delete_callback_thread(int a0);
int ChangeThreadPriority(int thid, int prio);

extern int D_00167EC0[];    /* .bss 0x00167EC0, 0x40 bytes, lui/%lo */
extern int D_00167F00[];    /* .bss 0x00167F00, 0x1000 bytes, lui/%lo */

int sceNetcnfifCreateCallbackThread(int *a0, int a1, int a2, int a3) {
    int h;
    int r;

    if (a0 == 0)
        return -0x65;
    h = sce_create_callback_thread((int)a0, a1, a2, 1);
    if (h < 0)
        return -1;
    sceNetcnfifInit();
    D_00167F00[2] = *a0;
    r = sceSifCallRpc((int)D_00167EC0, 0xB, 0, (int)D_00167F00, 0x1000,
                      (int)D_00167F00, 0x1000, 0, 0);
    if (r < 0) {
        sce_delete_callback_thread(h);
        return r;
    }
    ChangeThreadPriority(h, a3);
    return h;
}
