/* KERNEL.XFF @ 0x0126D8 (64 B) - iosSetDCClearParam
 * Evidence: bit 0 of the u64 at +0x170 replaced by (enable & 1) (and -2 / or),
 * four bytes +0x16C..+0x16F from $a2/$a3/$t0/$t1, then the same sibling call
 * as iosSetDCParam. UNCONFIRMED: field names.
 */
struct DCClear {
    char pad[0x16C];
    unsigned char r, g, b, a;
    unsigned long enable : 1;
};
void func_012280(struct DCClear *dc);

void iosSetDCClearParam(struct DCClear *dc, int enable, int r, int g, int b, int a) {
    dc->enable = enable;
    dc->r = r;
    dc->g = g;
    dc->b = b;
    dc->a = a;
    func_012280(dc);
}
