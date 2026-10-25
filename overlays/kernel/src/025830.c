/* KERNEL.XFF @ 0x025830 (28 B) - Sg2RemoteSyncStatus
 * Evidence: sibling sceSifCheckStatRpc(&.bss+0x96F00) (the RPC client data).
 */
extern char D_kernel_bss_96F00[];
int sceSifCheckStatRpc(void *cd);

int Sg2RemoteSyncStatus(void) {
    return sceSifCheckStatRpc(D_kernel_bss_96F00);
}
