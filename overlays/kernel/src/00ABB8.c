/* KERNEL.XFF @ 0x00ABB8 (60 B) - initDldSys
 * Evidence: writes -1 to word 0 of each of the eight 8-byte records at .bss+0xDE68, walking down from index 7 (pointer starts at +0x38, step -8). The -1 is materialised before the counter, as with a separate local. The nops are the R5900 short-loop padding. UNCONFIRMED: record layout.
 */
struct FileEnt {
    int id;
    int size;
};
extern struct FileEnt D_kernel_bss_DE68[8];

void initDldSys(void) {
    int i;
    int none = -1;

    for (i = 7; i >= 0; i--) {
        D_kernel_bss_DE68[i].id = none;
    }
}
