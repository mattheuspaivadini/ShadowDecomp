/* KERNEL.XFF @ 0x008CA8 (436 B) - func_008CA8 (static, no symbol in the shipped .symtab)
 * Evidence: computes two header sizes from the descriptor (+0xC byte, +0x1C, +0x24)
 * as (n << 4) + 0x33 blocks, creates a module object with
 * _isysCreateObj(arg, 2, 0x40, strlen(name) + size + 1, 0, 4), stores descriptor +0x10
 * into +0x20 and the descriptor pointer into +0x1C, clears flags
 * 0x80000000/0x40000000/0x20000000 in +0x2C (three separate `and`s after one load),
 * links the .data+0x390 group when +0x24 and the .data+0x388 group when +0x1C are
 * set, calls static .text+0x7930(obj, obj->0) and static .text+0x7F48(obj+0x30,
 * rootPtn, desc), then stores the malloc'd+strcpy'd name in +0x38 (else loads the
 * pointer kept at .data+0x374) and links .data+0x380; +0x3C = 0. Caller
 * InitDld (0x9490) passes (info.region, info., rootPtn). UNCONFIRMED: function name,
 * struct/field names, the callee prototypes.
 */
struct DldDesc {
    char pad00[0x0C];
    unsigned char n0C;
    char pad0D[3];
    int f10;
    char pad14[8];
    int f1C;
    char pad20[4];
    int f24;
};
struct ModuleObj {
    int ident;
    char pad04[0x18];
    struct DldDesc *desc;
    int f20;
    char pad24[8];
    unsigned int flags;
    char pad30[8];
    void *name;
    int f3C;
};
extern char rootPtn[];
extern int D_kernel_data_0374;
extern char D_kernel_data_0380[];
extern char D_kernel_data_0388[];
extern char D_kernel_data_0390[];
unsigned int strlen(const char *s);
char *strcpy(char *d, const char *s);
struct ModuleObj *_isysCreateObj(void *arg, int a, int b, int size, int c, int d);
int isysAddGroupWithLinkParam(struct ModuleObj *o, void *group, int a, int b);
void *iosMallocAlign();
void func_007930(struct ModuleObj *o, int ident);
void func_007F48(void *p, char *ptn, struct DldDesc *d);

struct ModuleObj *func_008CA8(char *name, struct DldDesc *d, void *arg) {
    struct ModuleObj *o;
    int n;
    int dif;
    int sz1;
    int sz2;

    n = d->n0C ? d->n0C + 1 : 2;
    dif = d->f24 - d->f1C - n;
    if (dif != 0) {
        sz1 = (dif << 4) + 0x33;
    } else {
        sz1 = 0;
    }
    if (d->f1C != 0) {
        sz2 = sz1 + (d->f1C << 4) + 0x33;
    } else {
        sz2 = sz1;
    }
    o = _isysCreateObj(arg, 2, 0x40, strlen(name) + sz2 + 1, 0, 4);
    o->f20 = d->f10;
    o->desc = d;
    o->flags &= 0x7FFFFFFF;
    o->flags &= 0xBFFFFFFF;
    o->flags &= 0xDFFFFFFF;
    if (d->f24) {
        isysAddGroupWithLinkParam(o, D_kernel_data_0390, 0, 0);
    }
    if (d->f1C) {
        isysAddGroupWithLinkParam(o, D_kernel_data_0388, 0, 0);
    }
    func_007930(o, o->ident);
    func_007F48((char *)o + 0x30, rootPtn, d);
    if (name != 0) {
        o->name = iosMallocAlign(o->ident, strlen(name) + 1, 1);
        strcpy(o->name, name);
    } else {
        o->name = (void *)D_kernel_data_0374;
    }
    isysAddGroupWithLinkParam(o, D_kernel_data_0380, 0, 0);
    o->f3C = 0;
    return o;
}
