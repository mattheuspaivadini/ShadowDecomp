/* KERNEL.XFF @ 0x0257B8 (32 B) - Sg2RemoteDmaTransStatus
 * Evidence: returns word 0 of the 20-byte record [ch] at .bss+0x96F50.
 */
struct DmaTrans {
    int status;
    int unk[4];
};
extern struct DmaTrans D_kernel_bss_96F50[];

int Sg2RemoteDmaTransStatus(int ch) {
    return D_kernel_bss_96F50[ch].status;
}
