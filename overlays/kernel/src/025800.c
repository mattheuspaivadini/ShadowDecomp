/* KERNEL.XFF @ 0x025800 (24 B) - Sg2RemoteGetSlotReleaseLv
 * Evidence: returns the word [i] of the table at .bss+0x96D40.
 */
extern int D_kernel_bss_96D40[];

int Sg2RemoteGetSlotReleaseLv(int i) {
    return D_kernel_bss_96D40[i];
}
