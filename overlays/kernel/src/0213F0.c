/* KERNEL.XFF @ 0x0213F0 (92 B) - Sg2ExStAdpcmTickProc
 * Evidence: remembers +0x22C, runs the statics at .text+0x20F98 and +0x21160, and repeats the first one (sibling) when +0x22C changed. UNCONFIRMED: callee names.
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
void func_020F98(struct ExStAdpcm *w);
void func_021160(struct ExStAdpcm *w);

void Sg2ExStAdpcmTickProc(struct ExStAdpcm *w) {
    int old = w->wrSlot;

    func_020F98(w);
    func_021160(w);
    if (w->wrSlot != old) {
        func_020F98(w);
    }
}
