/* KERNEL.XFF @ 0x020C20 (36 B) - Sg2ExStAdpcmCont
 * Evidence: restores state from +4 and calls Sg2StAdpcmSetPitch(u64 +0xA0, word +0x30). UNCONFIRMED: ExStAdpcm field names (offsets from this and the sibling accessors).
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

int Sg2ExStAdpcmCont(struct ExStAdpcm *w) {
    w->state = w->saved;
    return Sg2StAdpcmSetPitch(w->voice, w->pitch);
}
