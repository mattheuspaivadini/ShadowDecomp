/* KERNEL.XFF @ 0x02D9E8 (68 B) - vab_get_lfotbl_param
 * Evidence: *a = entry[id].+0x24, *tbl = entry[id].+0x20 (both loaded before the stores), returns entry[id].+0x28. The eight VAB entries are 44-byte records at .bss+0x9BCC0 (id * 11 * 4). UNCONFIRMED: field names.
 */
struct Sg2VabVel {
    int seMasterVol;
    int unk14;
    int tbl;
    int num;
};
struct Sg2VabLfo {
    int tbl;
    int a;
    int num;
};
struct Sg2VabEnt {
    int alive;
    int unk4;
    int unk8;
    int info;
    struct Sg2VabVel vel;
    struct Sg2VabLfo lfo;
};
extern struct Sg2VabEnt D_kernel_bss_9BCC0[8];

int vab_get_lfotbl_param(int id, int *tbl, int *a) {
    int va = D_kernel_bss_9BCC0[id].lfo.a;
    int vt = D_kernel_bss_9BCC0[id].lfo.tbl;

    *a = va;
    *tbl = vt;
    return D_kernel_bss_9BCC0[id].lfo.num;
}
