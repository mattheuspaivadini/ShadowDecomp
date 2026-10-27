/* KERNEL.XFF @ 0x01AAF0 (184 B) - _isysCreateObj
 * Evidence: iosCreatePartitionWithPc(parent, size + extra + 0x24, caller pc) (pc read from $ra at entry, register variable); iosMallocAlign(part, size, align) for the object; fills part (+0), pc (+4), type byte (+8), ref byte (+9), the bit-16 flag and 15-bit lock of word +8 (cleared together: lhu/sw), +0x14 = arg, +0x18 = 0, halfwords +0xE/+0xC = 0; returns the object or 0. UNCONFIRMED: field names other than lock (isysObjDeleteLock).
 */
struct Obj {
    void *part;
    void *pc;
    unsigned int type : 8;
    unsigned int ref : 8;
    unsigned int f16 : 1;
    unsigned int lock : 15;
    short unkC;
    short unkE;
    int unk10;
    int unk14;
    int unk18;
};
void *iosCreatePartitionWithPc(void *parent, int size, void *pc);
void *iosMallocAlign(void *ptn, int size, int align);

struct Obj *_isysCreateObj(void *parent, int type, int size, int extra, int arg, int align) {
    register void *ra __asm__("$31");
    void *pc = ra;
    void *part;
    struct Obj *obj;

    part = iosCreatePartitionWithPc(parent, size + extra + 0x24, pc);
    if (part == 0) {
        return 0;
    }
    obj = iosMallocAlign(part, size, align);
    if (obj == 0) {
        return 0;
    }
    obj->part = part;
    obj->pc = pc;
    obj->type = type;
    obj->ref = 0;
    obj->f16 = 0;
    obj->lock = 0;
    obj->unkE = 0;
    obj->unkC = 0;
    obj->unk14 = arg;
    obj->unk18 = 0;
    return obj;
}
