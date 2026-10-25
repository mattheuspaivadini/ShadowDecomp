/* KERNEL.XFF @ 0x01AD10 (40 B) - isysObjDeleteUnLock
 * Evidence: decrements the 15-bit field in bits 17..31 of word +8 (bitfield, see isysObjDeleteLock). UNCONFIRMED: field names.
 */
struct Obj {
    int unk0;
    int unk4;
    unsigned int low : 17;
    unsigned int lock : 15;
};
void isysObjDeleteUnLock(struct Obj *obj) {
    obj->lock--;
}
