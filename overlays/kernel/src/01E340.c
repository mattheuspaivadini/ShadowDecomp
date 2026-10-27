/* KERNEL.XFF @ 0x01E340 (88 B) - sndSepSetPan
 * Evidence: pan clamped to [-1, 1] (else-if: the second test is skipped after the first clamp), then stored as (float)(int)(pan * 63 + 64) to +0x24. UNCONFIRMED: field names.
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

void sndSepSetPan(struct SndSep *s, float pan) {
    if (1.0f < pan) {
        pan = 1.0f;
    } else if (pan < -1.0f) {
        pan = -1.0f;
    }
    s->pan = (int)(pan * 63.0f + 64.0f);
}
