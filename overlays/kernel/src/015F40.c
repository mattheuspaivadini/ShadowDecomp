/* KERNEL.XFF @ 0x015F40 (76 B) - iosGsChangeMode
 * Evidence: inlined copy of iosResetGraph(0, .data+0x5A0, .data+0x5A4, .data+0x5A8) (GS CSR = 0x200, sceGsResetGraph(0, inter & 1, omode, ffmode & 1)), then tail call to the static at .text+0x14910. UNCONFIRMED: names of the three short globals.
 */
extern short D_kernel_data_05A0;
extern short D_kernel_data_05A4;
extern short D_kernel_data_05A8;
void sceGsResetGraph(short mode, short inter, short omode, short ffmode);
void func_014910(void);

static inline void iosResetGraph(short mode, short inter, short omode, short ffmode) {
    if (mode != 0) {
        *(volatile unsigned long *)0x12001000 = 0x100;
        return;
    }
    *(volatile unsigned long *)0x12001000 = 0x200;
    sceGsResetGraph(0, inter & 1, omode, ffmode & 1);
}

void iosGsChangeMode(void) {
    iosResetGraph(0, D_kernel_data_05A0, D_kernel_data_05A4, D_kernel_data_05A8);
    func_014910();
}
