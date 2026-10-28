/* KERNEL.XFF @ 0x020920 (256 B) - Sg2ExStAdpcmTrkDspSw
 * Evidence: -1 for state < 0x10; sw == -1 takes the track default (+0x80 [trk]); finds the trk-th set voice bit of the u64 mask (+0xA0, loaded once, literal 1L) and switches its reverb with Sg2SlotSetReverbOffBit (sw 0) or Sg2SlotSetReverbOnBit (sw 1) on (core, bit), returning 0; -1 when no voice. UNCONFIRMED: field names.
 */
struct ExStAdpcm {
    int state;
    char pad4[0x7C];
    int dsp[8];
    unsigned long voice;
};
void Sg2SlotSetReverbOffBit(int core, unsigned int bits);
void Sg2SlotSetReverbOnBit(int core, unsigned int bits);

int Sg2ExStAdpcmTrkDspSw(struct ExStAdpcm *w, int trk, int sw) {
    unsigned long i;
    unsigned long voice;

    if (w->state < 0x10) {
        return -1;
    }
    if (sw == -1) {
        sw = w->dsp[trk];
    }
    voice = w->voice;
    for (i = 0; i < 48; i++) {
        if (voice & (1L << (int)i)) {
            if (--trk < 0) {
                switch (sw) {
                case 0:
                    Sg2SlotSetReverbOffBit(i >= 24, i < 24 ? 1 << (int)i : 1 << (int)(i - 24));
                    break;
                case 1:
                    Sg2SlotSetReverbOnBit(i >= 24, i < 24 ? 1 << (int)i : 1 << (int)(i - 24));
                    break;
                }
                return 0;
            }
        }
    }
    return -1;
}
