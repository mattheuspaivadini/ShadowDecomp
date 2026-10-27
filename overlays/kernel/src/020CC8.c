/* KERNEL.XFF @ 0x020CC8 (100 B) - Sg2ExStAdpcmIopReadAdr
 * Evidence: returns Sg2StAdpcmIopReadAdr(i) for the n-th set voice bit (--n < 0), else 0. The 48-bit voice mask (u64 +0xA0) is tested with (one << i) where one is a 64-bit 1 kept in a register and i a 64-bit counter (daddiu/sltiu); a literal 1UL lets GCC rewrite the test as (mask >> i) & 1.
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
int Sg2StAdpcmIopReadAdr(int ch);

int Sg2ExStAdpcmIopReadAdr(struct ExStAdpcm *w, int n) {
    unsigned long i = 0;
    unsigned long one = 1;

    for (; i < 48; i++) {
        if (w->voice & (one << (int)i)) {
            if (--n < 0) {
                return Sg2StAdpcmIopReadAdr((int)i);
            }
        }
    }
    return 0;
}
