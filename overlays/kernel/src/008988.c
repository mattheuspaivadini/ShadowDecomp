/* KERNEL.XFF @ 0x008988 (492 B) - func_008988 (static, no symbol in the shipped .symtab)
 * STATUS: MATCHING [-G0 -fno-strict-aliasing] 0/123 words differ
 * Evidence: clears flag 0x80000000 in obj+0x2C, then calls the 8-argument static
 * .text+0x7B40(desc, obj, obj->ident, .text+0xA1D0, .text+0xA218, DldSysUndefSymbol,
 * .text+0x7788, 0); its result p (or the descriptor when p == 0) becomes the "module
 * record": obj+0x20 = p->0 / desc->0x10, obj+0x1C = p ? p : desc; flags get
 * 0x80000000/0x40000000 (only when p != 0)/0x20000000 reworked in one load-store chain,
 * the +0x40000000 bit coming from `b = (p != 0)` (sltu+sll+or, the same `b` guards the
 * p == 0 block). When p == 0 the .data+0x390 group is linked if desc->0x24, the
 * .data+0x388 group if desc->0x1C, then static .text+0x7930(obj, obj->ident) and
 * static .text+0x7F48(obj+0x30, rootPtn, desc). When p != 0 the original sign bit of
 * flags is restored ((flags & 0x7FFFFFFF) | (sign << 31), sign = flags >> 31). The name
 * is strdup'd through iosMallocAlign(obj->ident, strlen+1, 1) or taken from
 * .data+0x374; then .data+0x380 is linked, obj+0x3C = 0 and the function returns 1.
 * Sibling .text+0x8CA8 (matched) shares the descriptor/module-object layout.
 * Levers tried: flag chain as mem statements (splits into two stores -> 484 B);
 * local `f` accumulator (two stores); `if (p) flags |= 0x40000000` (branchy);
 * `q/v` merged in the if/else (2 s-regs, 456 B); ternary sign select. The match needs
 * the named `int b = (p != 0)` reused both in `flags |= b << 30` and `if (b == 0)`,
 * a separate `if (p != 0) sign = ...` before it, and `q = p ? p : d;` /
 * `v = p ? p->ident : d->f10;` ternaries (movn + branch).
 * UNCONFIRMED: prototype, struct/field names, the callees' prototypes (007B40 takes 8
 * arguments incl. the two allocators and DldSysUndefSymbol's value).
 */
struct DldDesc {
    int ident;
    char pad04[0x0C];
    int f10;
    char pad14[8];
    int f1C;
    int f20;
    int f24;
};
struct ModuleObj {
    int ident;
    char pad04[0x18];
    struct DldDesc *f1C;
    int f20;
    char pad24[0x08];
    unsigned int flags;
    char pad30[0x08];
    void *name;
    int f3C;
};
extern int DldSysUndefSymbol;
extern char rootPtn[];
extern int D_kernel_data_0374;
extern char D_kernel_data_0380[];
extern char D_kernel_data_0388[];
extern char D_kernel_data_0390[];
unsigned int strlen(const char *s);
char *strcpy(char *d, const char *s);
void *iosMallocAlign();
void *func_00A1D0(int size, int align);
void *func_00A218(int size);
int func_007788(const char *fmt, ...);
struct DldDesc *func_007B40(struct DldDesc *d, struct ModuleObj *o, int ident,
                             void *a, void *b, int c, void *f, int e);
int isysAddGroupWithLinkParam(struct ModuleObj *o, void *group, int a, int b);
void func_007930(struct ModuleObj *o, int ident);
void func_007F48(void *p, char *ptn, struct DldDesc *d);

int func_008988(struct ModuleObj *o, char *name, struct DldDesc *d) {
    struct DldDesc *q;
    struct DldDesc *p;
    int sign = 0;
    int v;
    int b;

    o->flags &= 0x7FFFFFFF;
    p = func_007B40(d, o, o->ident, func_00A1D0, func_00A218, DldSysUndefSymbol,
                    func_007788, 0);
    if (p != 0)
        sign = (int)o->flags >> 31;
    q = p ? p : d;
    v = p ? p->ident : d->f10;
    o->f20 = v;
    o->f1C = q;
    b = (p != 0);
    o->flags &= 0x7FFFFFFF;
    o->flags &= 0xBFFFFFFF;
    o->flags |= b << 30;
    o->flags &= 0xDFFFFFFF;
    if (b == 0) {
        if (q->f24)
            isysAddGroupWithLinkParam(o, D_kernel_data_0390, 0, 0);
        if (q->f1C)
            isysAddGroupWithLinkParam(o, D_kernel_data_0388, 0, 0);
        func_007930(o, o->ident);
        func_007F48((char *)o + 0x30, rootPtn, q);
    }
    if (p != 0)
        o->flags = (o->flags & 0x7FFFFFFF) | (sign << 31);
    if (name != 0) {
        o->name = iosMallocAlign(o->ident, strlen(name) + 1, 1);
        strcpy(o->name, name);
    } else {
        o->name = (void *)D_kernel_data_0374;
    }
    isysAddGroupWithLinkParam(o, D_kernel_data_0380, 0, 0);
    o->f3C = 0;
    return 1;
}
