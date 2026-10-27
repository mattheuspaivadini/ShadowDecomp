/* KERNEL.XFF @ 0x02DB98 (104 B) - Sg2VabBdOpen
 * Evidence: -1 unless vab_check_alive(id); then entry[id].+0xC = bd and 0. The eight VAB entries are 44-byte records at .bss+0x9BCC0. UNCONFIRMED: field names.
 */
struct Sg2VabHdr {
    int unk0;
    int bdSize;
};
struct Sg2VabEnt {
    int alive;
    int unk4;
    int unk8;
    void *bd;
    int seMasterVol;
    struct Sg2VabHdr *hdr;
    char pad[0x2C - 0x18];
};
extern struct Sg2VabEnt D_kernel_bss_9BCC0[8];
int vab_check_alive(int id);

int Sg2VabBdOpen(int id, void *bd) {
    struct Sg2VabEnt *e = &D_kernel_bss_9BCC0[id];

    if (!vab_check_alive(id)) {
        return -1;
    }
    e->bd = bd;
    return 0;
}
