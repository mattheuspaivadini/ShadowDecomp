/* KERNEL.XFF @ 0x020B60 (120 B) - Sg2ExStAdpcmPlay
 * Evidence: in state 8: state = 0x10, r = Sg2StAdpcmPlay(u64 voice +0xA0), ____VolReflection(w), Sg2ExStAdpcmPitchPercent(w, +0x2CC), return r; otherwise flag 4 is set in +8 and r is returned uninitialised (as in the original). UNCONFIRMED: field names.
 */
struct ExStAdpcm {
    int state;
    int saved;
    int flags;
    int flagsInit;
    char pad10[0x18];
    int magic;
    char pad2C[0x74];
    unsigned long voice;
    char padA8[0x180];
    int unk228;
    int unk22C;
    char pad230[0x18];
    int pos;
    char pad24C[0x80];
    int pitchPercent;
    char pad2D0[4];
    int unk2D4;
};
int Sg2StAdpcmPlay(unsigned long voice);
void ____VolReflection(struct ExStAdpcm *w);
int Sg2ExStAdpcmPitchPercent(struct ExStAdpcm *w, int percent);

int Sg2ExStAdpcmPlay(struct ExStAdpcm *w) {
    int r;

    if (w->state == 8) {
        w->state = 0x10;
        r = Sg2StAdpcmPlay(w->voice);
        ____VolReflection(w);
        Sg2ExStAdpcmPitchPercent(w, w->pitchPercent);
    } else {
        w->flags |= 4;
    }
    return r;
}
