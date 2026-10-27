/* KERNEL.XFF @ 0x01E2E8 (24 B) - sndSepStopReq
 * Evidence: sets bit 32 of the u64 at +8 (0x8000 << 17).
 */
struct SndSep {
    long unk0;
    unsigned long flags;
};

void sndSepStopReq(struct SndSep *s) {
    s->flags |= 0x100000000UL;
}
