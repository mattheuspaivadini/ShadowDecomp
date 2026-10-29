/* KERNEL.XFF @ 0x02D9B0 (56 B) - vab_get_veltbl
 * STATUS: NOT MATCHING, 14/14 words but 3 differ. Image order is lw a2(tbl), daddu v1,a0, lw v0(num), sw; every variant tried puts the daddu copy
 * (and the num load) before the tbl load, or drops the copy (48 B): two locals, pointer vars, e/f copy, unsigned id, num-first, inline block.
 * Not in c_sources.txt.
 * Evidence: *tbl = entry[id].vel.tbl (loaded before the store), returns entry[id].vel.num; same 44-byte VAB records at .bss+0x9BCC0 as vab_get_lfotbl_param. UNCONFIRMED: field names.
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

int vab_get_veltbl(int id, int *tbl) {
    int vt = D_kernel_bss_9BCC0[id].vel.tbl;

    *tbl = vt;
    return D_kernel_bss_9BCC0[id].vel.num;
}
