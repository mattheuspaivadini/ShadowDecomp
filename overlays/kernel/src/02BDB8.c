/* KERNEL.XFF @ 0x02BDB8 (104 B) - Sg2SmfpStop
 * Evidence: for a playing player (status 2): Sg2SmfpPause(id, 0), Sg2SmfpCont(id), status = 1; returns 0. The eight SMF players are 0x80-byte records at .bss+0x9A880 (status +0, module +8, vab +0xC). UNCONFIRMED: names.
 */
struct Sg2Smfp {
    int status;
    int unk4;
    int mod;
    int vab;
    char pad[0x80 - 0x10];
};
extern struct Sg2Smfp D_kernel_bss_9A880[8];
int Sg2SmfpPause(int id, int mode);
int Sg2SmfpCont(int id);

int Sg2SmfpStop(int id) {
    struct Sg2Smfp *p;

    if (id >= 0) {
        p = &D_kernel_bss_9A880[id];
        if (p->status == 2) {
            Sg2SmfpPause(id, 0);
            Sg2SmfpCont(id);
            p->status = 1;
        }
    }
    return 0;
}
