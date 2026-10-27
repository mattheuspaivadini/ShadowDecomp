/* KERNEL.XFF @ 0x02C7E0 (132 B) - Sg2SmfpInit
 * Evidence: fills the eight player records with 0xFF (memset -1) and clears each status; .bss+0x9AC84 = 1, .bss+0x9BCA0 = 0, .bss+0x9AC88 = 0; Sg2CtrlEntryTickProcById(0, static .text+0x2C4F0); returns 0. The eight SMF players are 0x80-byte records at .bss+0x9A880 (status +0, module +8, vab +0xC). UNCONFIRMED: names.
 */
struct Sg2Smfp {
    int status;
    int unk4;
    int mod;
    int vab;
    char pad[0x80 - 0x10];
};
extern struct Sg2Smfp D_kernel_bss_9A880[8];
extern int D_kernel_bss_9AC84;
extern int D_kernel_bss_9BCA0;
extern int D_kernel_bss_9AC88;
void *memset(void *p, int c, unsigned int n);
void func_02C4F0(void);
int Sg2CtrlEntryTickProcById(int id, void (*func)(void));

int Sg2SmfpInit(void) {
    struct Sg2Smfp *p = D_kernel_bss_9A880;
    int i;

    for (i = 7; i >= 0; i--, p++) {
        memset(p, -1, sizeof(*p));
        p->status = 0;
    }
    D_kernel_bss_9AC84 = 1;
    D_kernel_bss_9BCA0 = 0;
    D_kernel_bss_9AC88 = 0;
    Sg2CtrlEntryTickProcById(0, func_02C4F0);
    return 0;
}
