/* KERNEL.XFF @ 0x02BB00 (88 B) - Sg2SmfpClose
 * Evidence: for id >= 0: if the 0x80-byte SMF record [id] (.bss+0x9A880) is active, Sg2SmfpStopSndOff(id); Sg2ModClose(record.mod); status = 0; returns 0.
 */
struct Sg2Smfp {
    int status;
    int unk4;
    int mod;
    int vab;
    char pad[0x80 - 0x10];
};
extern struct Sg2Smfp D_kernel_bss_9A880[8];
int Sg2SmfpStopSndOff(int id);
int Sg2ModClose(int mod);

int Sg2SmfpClose(int id) {
    struct Sg2Smfp *p;

    if (id >= 0) {
        p = &D_kernel_bss_9A880[id];
        if (p->status) {
            Sg2SmfpStopSndOff(id);
        }
        Sg2ModClose(p->mod);
        p->status = 0;
    }
    return 0;
}
