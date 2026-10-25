/* KERNEL.XFF @ 0x020BD8 (68 B) - Sg2ExStAdpcmPause
 * Evidence: returns -1 when state (+0) is already 0x80; else saves state to +4, sets 0x80 and calls Sg2StAdpcmSetPitch(u64 +0xA0, 0). UNCONFIRMED: ExStAdpcm field names (offsets from this and the sibling accessors).
 */
struct ExStAdpcm {
    int state;
    int saved;
    char pad08[0x28];
    int pitch;
    char pad34[4];
    int loopStart;
    int loopEnd;
    char pad40[0x60];
    long voice;
    char padA8[0x184];
    int wrSlot;
    int buf0;
    int buf1;
    int buf2;
    int buf3;
    char pad240[8];
    unsigned int pos;
    char pad24C[0x80];
    int pitchPercent;
    char pad2D0[8];
    int lsn;
    int userParam;
};
int Sg2StAdpcmSetPitch(long voice, int pitch);

int Sg2ExStAdpcmPause(struct ExStAdpcm *w) {
    if (w->state == 0x80) {
        return -1;
    }
    w->saved = w->state;
    w->state = 0x80;
    return Sg2StAdpcmSetPitch(w->voice, 0);
}
