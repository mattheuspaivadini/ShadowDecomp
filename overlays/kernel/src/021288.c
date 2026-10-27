/* KERNEL.XFF @ 0x021288 (144 B) - Sg2ExStAdpcmPreLoad
 * Evidence: returns -1 unless state (+0) is 1; state = 2; static .text+0x20DB0(p, 2, 0, 0) unless flag bit 0 (+8); then (p, 1, +0x230, +0x234); then (p, 0x10, 0, 0) when flag 0x10. Returns 0. UNCONFIRMED: field names, static prototype.
 */
struct StAdpcm {
    int state;
    int unk4;
    unsigned int flags;
    char pad[0x230 - 0xC];
    int unk230;
    int unk234;
};
static int func_020DB0(struct StAdpcm *p, int cmd, int a, int b);

int Sg2ExStAdpcmPreLoad(struct StAdpcm *p) {
    if (p->state != 1) {
        return -1;
    }
    p->state = 2;
    if (!(p->flags & 1)) {
        func_020DB0(p, 2, 0, 0);
    }
    func_020DB0(p, 1, p->unk230, p->unk234);
    if (p->flags & 0x10) {
        func_020DB0(p, 0x10, 0, 0);
    }
    return 0;
}
