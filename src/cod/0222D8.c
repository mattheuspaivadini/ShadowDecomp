/* asm/cod/0222D8.s -> sceNetcnfifDeleteCallbackThread.
 * SCE SDK, cc=29 (callee return types / statement shape from the image)
 * MATCHED. */
int sce_delete_callback_thread(int a0);
int sceNetcnfifInit(void);
int sceSifCallRpc(int a0, int a1, int a2, int a3, int a4, int a5, int a6,
                  int a7, int a8);

extern char D_00167EC0[];   /* .bss 0x00167EC0, 0x40 bytes */
extern char D_00167F00[];   /* .bss 0x00167F00, 0x1000 bytes */

int sceNetcnfifDeleteCallbackThread(int a0) {
    int r;
    int st;

    sce_delete_callback_thread(a0);
    sceNetcnfifInit();
    r = sceSifCallRpc((int)D_00167EC0, 0xF, 0, (int)D_00167F00, 0x1000,
                      (int)D_00167F00, 0x1000, 0, 0);
    st = 0;
    if (r <= -1)
        st = r;
    return st;
}
