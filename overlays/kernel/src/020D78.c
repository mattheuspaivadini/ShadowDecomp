/* KERNEL.XFF @ 0x020D78 (40 B) - Sg2ExStAdpcmGetBuffer
 * Evidence: copies words +0x230..+0x23C to the four out pointers (5th in $t0), returns 0. UNCONFIRMED: ExStAdpcm field names (offsets from this and the sibling accessors).
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

int Sg2ExStAdpcmGetBuffer(struct ExStAdpcm *w, int *b0, int *b1, int *b2, int *b3) {
    *b0 = w->buf0;
    *b1 = w->buf1;
    *b2 = w->buf2;
    *b3 = w->buf3;
    return 0;
}
