/* KERNEL.XFF @ 0x02DA60 (40 B) - vab_get_semastervol
 * Evidence: returns entry[id].+0x10. The eight VAB entries are 44-byte records at .bss+0x9BCC0 (id * 11 * 4). UNCONFIRMED: field names.
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

int vab_get_semastervol(int id) {
    return D_kernel_bss_9BCC0[id].seMasterVol;
}
