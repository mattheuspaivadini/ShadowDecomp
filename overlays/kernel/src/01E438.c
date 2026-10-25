/* KERNEL.XFF @ 0x01E438 (36 B) - sndSepCont
 * Evidence: clears bit 33 of the u64 at +8 (mask ~(1 << 33) built with dsll/ori).
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

void sndSepCont(struct SndSep *s) {
    s->flags &= ~0x200000000UL;
}
