/* KERNEL.XFF @ 0x02DA88 (136 B) - Sg2VabHdOpen
 * Evidence: under DIntr/EIntr: id = get_vabid(); the static at .text+0x2D570 opens the header into entry[id]; returns id unless it returned -1 (xor/movn with -1). The eight VAB entries are 44-byte records at .bss+0x9BCC0. UNCONFIRMED: field names.
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
int DIntr(void);
int EIntr(void);
int get_vabid(void);
int func_02D570(struct Sg2VabEnt *e, void *hd);

int Sg2VabHdOpen(void *hd) {
    int intr = DIntr();
    int id = get_vabid();
    int ret;

    ret = (func_02D570(&D_kernel_bss_9BCC0[id], hd) != -1) ? id : -1;
    if (intr) {
        EIntr();
    }
    return ret;
}
