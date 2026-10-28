/* KERNEL.XFF @ 0x00A288 (140 B) - func_00A288 (static, no symbol in the shipped .symtab)
 * Evidence: for a non-NULL object, frees the data (+0) of every allocated (+0x18) 0x20-byte section entry after the first (table +0x30, count +0x40; explicit count-down loop), clearing the flag, then frees the object; returns it. UNCONFIRMED: names; Ghidra FUN_0020a288.
 */
struct SectEnt {
    void *data;
    char pad4[0x14];
    int alloc;
    char pad1C[4];
};
struct SectObj {
    char pad0[0x30];
    struct SectEnt *sect;
    char pad34[0xC];
    int num;
};
void iosFree(void *p);

struct SectObj *func_00A288(struct SectObj *obj) {
    struct SectEnt *e;
    int i;

    if (obj) {
        e = &obj->sect[1];
        for (i = obj->num - 2; i != -1; i--, e++) {
            if (e->alloc) {
                e->alloc = 0;
                iosFree(e->data);
            }
        }
        iosFree(obj);
    }
    return obj;
}
