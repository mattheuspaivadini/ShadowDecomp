/* KERNEL.XFF @ 0x02BF60 (40 B) - Sg2SmfpStatus
 * Evidence: returns word 0 of the 128-byte record [id] at .bss+0x9A880 for id >= 0, else 1. UNCONFIRMED: names.
 */
struct Sg2Smfp {
    int status;
    int unk4;
    int mod;
    char pad[0x80 - 0xC];
};
extern struct Sg2Smfp D_kernel_bss_9A880[];

int Sg2SmfpStatus(int id) {
    if (id >= 0) {
        return D_kernel_bss_9A880[id].status;
    }
    return 1;
}
