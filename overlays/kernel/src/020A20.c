/* KERNEL.XFF @ 0x020A20 (140 B) - ____VolReflection
 * Evidence: for state >= 0x10, the static at .text+0x20598 is called as (w, i, n++) for every voice bit i set. The 48-bit voice mask (u64 +0xA0) is tested with (one << i) where one is a 64-bit 1 kept in a register and i a 64-bit counter (daddiu/sltiu); a literal 1UL lets GCC rewrite the test as (mask >> i) & 1.
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
void func_020598(struct ExStAdpcm *w, int ch, int n);

void ____VolReflection(struct ExStAdpcm *w) {
    unsigned long i;
    int n;
    unsigned long one;

    if (w->state < 0x10) {
        return;
    }
    i = 0;
    n = 0;
    one = 1;
    for (; i < 48; i++) {
        if (w->voice & (one << (int)i)) {
            func_020598(w, (int)i, n++);
        }
    }
}
