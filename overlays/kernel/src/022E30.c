/* KERNEL.XFF @ 0x022E30 (124 B) - Sg2ModInit
 * Evidence: clears each of the 32 0x9B0-byte module records at .bss+0x7F6D8 (memset) and calls the static initialiser at .text+0x21450 with its index; .bss+0x92CD8 = 1; Sg2CtrlEntryTickProcById(2, static .text+0x21B58); returns 0.
 */
struct Sg2Mod {
    char pad[0x9B0];
};
extern struct Sg2Mod D_kernel_bss_7F6D8[32];
extern int D_kernel_bss_92CD8;
void *memset(void *p, int c, unsigned int n);
void func_021450(int id);
void func_021B58(void);
int Sg2CtrlEntryTickProcById(int id, void (*func)(void));

int Sg2ModInit(void) {
    int i;

    for (i = 0; i < 32; i++) {
        memset(&D_kernel_bss_7F6D8[i], 0, sizeof(struct Sg2Mod));
        func_021450(i);
    }
    D_kernel_bss_92CD8 = 1;
    Sg2CtrlEntryTickProcById(2, func_021B58);
    return 0;
}
