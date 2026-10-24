/* MANAGER.XFF @ 0x01E298 (20 B) - modelGetTextureObjByIndex
 * Evidence: lw v0,0x40(a0) / sll a1,a1,5 / addu a1,a1,v0 / jr / lw v0,0x10(a1):
 * an array of 32-byte records whose base pointer lives at +0x40; the result is
 * the word at +0x10 of the selected record. The 32-byte stride is expressed as
 * a record struct so the index scales with a shift. Record contents beyond the
 * +0x10 word are UNCONFIRMED padding.
 */
typedef struct {
    int pad0[4];
    int value;      /* +0x10 */
    int pad1[3];    /* to the 0x20 stride */
} ModelTextureObj;

int modelGetTextureObjByIndex(unsigned char *model, int index) {
    ModelTextureObj *base = *(ModelTextureObj **)(model + 0x40);
    return base[index].value;
}
