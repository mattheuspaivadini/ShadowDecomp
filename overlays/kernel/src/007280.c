/* KERNEL.XFF @ 0x007280 (56 B) - Init_ShockVoiceSet
 * Evidence: stores the header pointer, then three `hdr + (u16 field)*4` pointers
 * to +0xC/+4/+8 in that order. The loads and stores stay strictly in source
 * order, which only happens without type-based aliasing: built with
 * -fno-strict-aliasing. UNCONFIRMED: field names.
 */
void Init_ShockVoiceSet(int **vs, unsigned short *hdr) {
    vs[0] = (int *)hdr;
    vs[3] = (int *)hdr + hdr[5];
    vs[1] = (int *)hdr + hdr[1];
    vs[2] = (int *)hdr + hdr[3];
}
