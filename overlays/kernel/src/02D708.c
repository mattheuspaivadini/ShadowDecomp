/* KERNEL.XFF @ 0x02D708 (60 B) - vab_check_alive
 * Evidence: 0 for id < 0 or id >= 8 (two signed tests), else entry[id].+0 != 0. The eight VAB entries are 44-byte records at .bss+0x9BCC0 (id * 11 * 4). UNCONFIRMED: field names.
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

int vab_check_alive(int id) {
    if (id < 0) {
        return 0;
    }
    if (id >= 8) {
        return 0;
    }
    return D_kernel_bss_9BCC0[id].alive != 0;
}
