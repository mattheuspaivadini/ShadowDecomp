/* KERNEL.XFF @ 0x020550 (12 B) - Sg2ExStAdpcmSetLsn
 * Evidence: stores lsn at +0x2D8 and returns 0 (same word Sg2ExStAdpcmSetFd writes). UNCONFIRMED: ExStAdpcm field names (offsets from this and the sibling accessors).
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

int Sg2ExStAdpcmSetLsn(struct ExStAdpcm *w, int lsn) {
    w->lsn = lsn;
    return 0;
}
