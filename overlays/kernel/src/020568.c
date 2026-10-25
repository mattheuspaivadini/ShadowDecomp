/* KERNEL.XFF @ 0x020568 (20 B) - Sg2ExStAdpcmGetTargetLsn
 * Evidence: returns word +0x2D8 + (unsigned word +0x248 >> 11) (byte position to sectors). UNCONFIRMED: ExStAdpcm field names (offsets from this and the sibling accessors).
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

int Sg2ExStAdpcmGetTargetLsn(struct ExStAdpcm *w) {
    return w->lsn + (w->pos >> 11);
}
