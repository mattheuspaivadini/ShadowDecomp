/* KERNEL.XFF @ 0x0126B0 (40 B) - iosSetDCParam
 * Evidence: four stores (+0x160 w, +0x164 w, +0x168 h, +0x16A h from $a1..$a3 and
 * the 5th argument register $t0) then a sibling call to the static at
 * .text+0x12280 with the object. UNCONFIRMED: field names and types.
 */
struct DCParam {
    char pad[0x160];
    int x160;
    int x164;
    short x168;
    short x16A;
};
void func_012280(struct DCParam *dc);

void iosSetDCParam(struct DCParam *dc, int a, int b, short c, short d) {
    dc->x160 = a;
    dc->x164 = b;
    dc->x168 = c;
    dc->x16A = d;
    func_012280(dc);
}
