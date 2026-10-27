/* KERNEL.XFF @ 0x0257D8 (24 B) - Sg2RemoteGetAdpStmAdr
 * Evidence: returns the word [i] of the table at .bss+0x96E00.
 */
extern int D_kernel_bss_96E00[];

int Sg2RemoteGetAdpStmAdr(int i) {
    return D_kernel_bss_96E00[i];
}
