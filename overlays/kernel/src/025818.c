/* KERNEL.XFF @ 0x025818 (24 B) - Sg2RemoteGetDspChangeStatus
 * Evidence: returns the word [i] of the table at .bss+0x96EC8.
 */
extern int D_kernel_bss_96EC8[];

int Sg2RemoteGetDspChangeStatus(int i) {
    return D_kernel_bss_96EC8[i];
}
