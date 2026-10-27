/* KERNEL.XFF @ 0x02D530 (64 B) - get_vabid
 * Evidence: first VAB entry whose word 0 is 0, or -1. The eight VAB entries are 44-byte records at .bss+0x9BCC0 (id * 11 * 4). UNCONFIRMED: field names.
 */
struct Sg2VabEnt {
    int alive;
    int unk4;
    int unk8;
    int info;
    int seMasterVol;
    int unk14;
    int velTbl;
    int velNum;
    int lfoTbl;
    int lfoA;
    int lfoNum;
};
extern struct Sg2VabEnt D_kernel_bss_9BCC0[8];

int get_vabid(void) {
    int i;

    for (i = 0; i < 8; i++) {
        if (D_kernel_bss_9BCC0[i].alive == 0) {
            return i;
        }
    }
    return -1;
}
