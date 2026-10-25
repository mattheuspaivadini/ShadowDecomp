/* KERNEL.XFF @ 0x02DA30 (44 B) - vab_set_semastervol
 * Evidence: returns the old entry[id].+0x10 and stores the new SE master volume. The eight VAB entries are 44-byte records at .bss+0x9BCC0 (id * 11 * 4). UNCONFIRMED: field names.
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

int vab_set_semastervol(int id, int vol) {
    int old = D_kernel_bss_9BCC0[id].seMasterVol;

    D_kernel_bss_9BCC0[id].seMasterVol = vol;
    return old;
}
