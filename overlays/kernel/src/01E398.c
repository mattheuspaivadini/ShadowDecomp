/* KERNEL.XFF @ 0x01E398 (92 B) - sndSepSetDefaultParam
 * Evidence: fields at +0x8 = 0xC, +0x20 = -1.0f (0xBF800000), +0x24 = 64.0f
 * (0x42800000), +0x2A = -1, +0x2C = 0x1000, +0x2E = 1, +0x30 = 1, and
 * +0x28 = (short)(int)(+0x1C * 127.0f) (lwc1/mul.s/cvt.w.s/mfc1/sh); the
 * 0x1C store order comes from the scheduler (last store in the jr delay slot).
 * The -1 for +0x2A is materialised through a local: with a bare literal the
 * compiler swaps the 0xC/-1 pseudos into $v0/$v1 and the 0x2A/0x8 stores.
 * UNCONFIRMED: struct layout/field names beyond the touched offsets, and
 * whether the original really used a local for -1.
 */
struct SndSep {
    int unk0;
    int unk4;
    int mode;
    char pad0C[0x10];
    float vol;
    float pitch;
    float pan;
    short vol127;
    short unk2A;
    short unk2C;
    short unk2E;
    short unk30;
};

void sndSepSetDefaultParam(struct SndSep *s) {
    int neg = -1;

    s->mode = 12;
    s->unk2A = neg;
    s->pitch = -1.0f;
    s->pan = 64.0f;
    s->unk30 = 1;
    s->unk2E = 1;
    s->unk2C = 0x1000;
    s->vol127 = (short)(int)(s->vol * 127.0f);
}
