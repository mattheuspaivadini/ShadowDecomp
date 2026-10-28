/* KERNEL.XFF @ 0x00A408 (252 B) - func_00A408 (static, no symbol in the shipped .symtab)
 * Evidence: as func_00A318 with both paths joined, then the module size (+0x3C) is subtracted from the byte counter at .data+0x370. UNCONFIRMED: names; Ghidra FUN_0020a408.
 */
struct SectEnt {
    void *data;
    char pad4[0x14];
    int alloc;
    char pad1C[4];
};
struct SectObj {
    int unk0;
    void *image;
    char pad8[0x28];
    struct SectEnt *sect;
    char pad34[0xC];
    int num;
};
struct ModBuf {
    int used;
    void *ptr;
};
struct ModuleObj {
    char pad0[0x1C];
    struct SectObj *so;
    char pad20[0xC];
    unsigned int flags;
    struct ModBuf bf;
    char pad38[4];
    int size;
};
extern int D_kernel_data_0370;
void iosFree(void *p);
void func_0080D0(struct ModuleObj *m);

static __inline__ void freeModBuf(struct ModBuf *b) {
    if (b->ptr) {
        iosFree(b->ptr);
        b->used = 0;
    }
}

static __inline__ struct SectObj *freeSectObj(struct SectObj *obj) {
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

void func_00A408(struct ModuleObj *m) {
    if (m->flags & 0x40000000) {
        iosFree(m->so->image);
        func_0080D0(m);
    } else {
        freeModBuf(&m->bf);
        func_0080D0(m);
        freeSectObj(m->so);
    }
    D_kernel_data_0370 -= m->size;
}
