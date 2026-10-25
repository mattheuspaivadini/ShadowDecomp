/* KERNEL.XFF @ 0x01ACE8 (40 B) - isysObjDeleteLock
 * Evidence: increments the 15-bit field in bits 17..31 of word +8, preserving bits 0..16 (srl 17 / and 0x1FFFF / sll 17 / or): a bitfield. UNCONFIRMED: field names.
 */
struct Obj {
    int unk0;
    int unk4;
    unsigned int low : 17;
    unsigned int lock : 15;
};
void isysObjDeleteLock(struct Obj *obj) {
    obj->lock++;
}
