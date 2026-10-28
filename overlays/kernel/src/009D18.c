/* KERNEL.XFF @ 0x009D18 (228 B) - isysFlushModuleObj
 * Evidence: a module with flag 0x40000000 (+0x2C) frees its relocated image (+0x1C -> +4) and calls the static at .text+0x80D0; otherwise frees the image buffer (+0x34, clearing +0x30), calls the same static and, when the relocation block (+0x1C) exists, frees every used 0x20-byte segment buffer from index 1 (count +0x40, array +0x30, used flag +0x18) and the block itself; returns 0. UNCONFIRMED: field names.
 */
struct ModSeg {
    void *buf;
    char pad4[0x14];
    int used;
    int pad1c;
};
struct ModRel {
    char pad0[4];
    void *image;
    char pad8[0x28];
    struct ModSeg *seg;
    char pad34[0xC];
    int num;
};
struct ModImage {
    int size;
    void *buf;
};
struct ModuleObj {
    char pad0[0x1C];
    struct ModRel *rel;
    char pad20[0xC];
    unsigned int flags;
    struct ModImage img;
};
void iosFree(void *p);
void func_0080D0(struct ModuleObj *m);

int isysFlushModuleObj(struct ModuleObj *m) {
    struct ModRel *rel;
    struct ModSeg *seg;
    int i;
    struct ModImage *img;

    if (m->flags & 0x40000000) {
        iosFree(m->rel->image);
        func_0080D0(m);
    } else {
        img = &m->img;
        if (img->buf != 0) {
            iosFree(img->buf);
            img->size = 0;
        }
        func_0080D0(m);
        rel = m->rel;
        if (rel != 0) {
            seg = &rel->seg[1];
            for (i = rel->num - 2; i != -1; i--) {
                if (seg->used) {
                    seg->used = 0;
                    iosFree(seg->buf);
                }
                seg++;
            }
            iosFree(rel);
        }
    }
    return 0;
}
