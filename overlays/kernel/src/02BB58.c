/* KERNEL.XFF @ 0x02BB58 (108 B) - Sg2SmfpVabStopSndOff
 * Evidence: when vab_check_alive(vab), Sg2SmfpClose(i) for every player whose +0xC equals vab (record-pointer loop); returns 0. The eight SMF players are 0x80-byte records at .bss+0x9A880 (status +0, module +8, vab +0xC). UNCONFIRMED: names.
 */
struct Sg2Smfp {
    int status;
    int unk4;
    int mod;
    int vab;
    char pad[0x80 - 0x10];
};
extern struct Sg2Smfp D_kernel_bss_9A880[8];
int vab_check_alive(int id);
int Sg2SmfpClose(int id);

int Sg2SmfpVabStopSndOff(int vab) {
    struct Sg2Smfp *p;
    int i;

    if (vab_check_alive(vab)) {
        p = D_kernel_bss_9A880;
        for (i = 0; i < 8; i++, p++) {
            if (p->vab == vab) {
                Sg2SmfpClose(i);
            }
        }
    }
    return 0;
}
