/* KERNEL.XFF @ 0x020D60 (24 B) - Sg2ExStAdpcmLoopSecNum
 * Evidence: *start = +0x38, *end = +0x3C, returns 0. UNCONFIRMED: ExStAdpcm field names (offsets from this and the sibling accessors).
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

int Sg2ExStAdpcmLoopSecNum(struct ExStAdpcm *w, int *start, int *end) {
    *start = w->loopStart;
    *end = w->loopEnd;
    return 0;
}
