/* KERNEL.XFF @ 0x020B00 (92 B) - Sg2ExStAdpcmPitchPercent
 * Evidence: stores percent at +0x2CC; returns -1 while state (+0) < 0x10; else sibling Sg2StAdpcmSetPitch(u64 +0xA0, word +0x30 * percent / 100) (GCC's divide-by-zero trap kept for the constant). UNCONFIRMED: ExStAdpcm field names (offsets from this and the sibling accessors).
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

int Sg2ExStAdpcmPitchPercent(struct ExStAdpcm *w, int percent) {
    w->pitchPercent = percent;
    if (w->state < 0x10) {
        return -1;
    }
    return Sg2StAdpcmSetPitch(w->voice, w->pitch * percent / 100);
}
