/* KERNEL.XFF @ 0x01E420 (24 B) - sndSepPause
 * Evidence: sets bit 33 of the u64 at +8 (0x8000 << 18). UNCONFIRMED: flag name.
 */
struct SndSep {
    int unk0;
    int unk4;
    unsigned long flags;
    char pad10[0xC];
    float vol;
    float pitch;
    float pan;
    short vol127;
    short unk2A;
    short unk2C;
    short unk2E;
    short unk30;
};

void sndSepPause(struct SndSep *s) {
    s->flags |= 0x200000000UL;
}
