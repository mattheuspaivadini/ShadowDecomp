/* KERNEL.XFF @ 0x0206A0 (184 B) - Sg2ExStAdpcmVolumePercent
 * Evidence: both words of the eight 8-byte volume pairs at +0x24C = vol (record pointer, +4 stored first); -1 for state < 0x10; else the static at .text+0x20598 (w, i, n++) for every voice bit i of the u64 at +0xA0, returning 0 once a voice was updated (ret starts at -1). UNCONFIRMED: field names.
 */
struct ExStVol {
    int l;
    int r;
};
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
    struct ExStVol vol[8];
    struct ExStVol volBackup[8];
};
void func_020598(struct ExStAdpcm *w, int ch, int n);

int Sg2ExStAdpcmVolumePercent(struct ExStAdpcm *w, int vol) {
    unsigned long i;
    int n;
    unsigned long one;
    int ret = -1;
    struct ExStVol *v = w->vol;

    for (i = 0; i < 8; i++, v++) {
        v->r = vol;
        v->l = vol;
    }
    if (w->state < 0x10) {
        return ret;
    }
    i = 0;
    n = 0;
    one = 1;
    for (; i < 48; i++) {
        if (w->voice & (one << (int)i)) {
            func_020598(w, (int)i, n++);
            ret = 0;
        }
    }
    return ret;
}
