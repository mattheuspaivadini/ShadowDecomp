/* KERNEL.XFF @ 0x030090 (28 B) - IirInit
 * Evidence: clears the five state words +0x1C..+0x2C and +0x30 of an IIR filter (the last independent store is emitted first). UNCONFIRMED: field names.
 */
struct Iir {
    char pad[0x1C];
    int z[5];
    int unk30;
};

void IirInit(struct Iir *f) {
    f->z[0] = 0;
    f->z[1] = 0;
    f->z[2] = 0;
    f->z[3] = 0;
    f->unk30 = 0;
    f->z[4] = 0;
}
