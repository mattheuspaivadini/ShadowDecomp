/* KERNEL.XFF @ 0x012590 (212 B) - iosCreateDC
 * Evidence: _isysCreateObj(parent, 0x1F, 0x24, num*400 + 0x33, .text+0x12A98, 0x10), immediate delete func .text+0x12AA0, +0x20 = num, +0x1C = iosMallocAlign(obj ptn, num*400, 0x10); each 400-byte DC array gets owner +0x184 and bits 0/1 of the 64-bit flags at +0x170 cleared; added to the group at .bss+0x1EAC8. UNCONFIRMED: field names.
 */
struct IosDC {
    char pad0[0x170];
    unsigned long flags;
    char pad178[0xC];
    struct DCObj *owner;
    char pad188[400 - 0x188];
};
struct DCObj {
    void *ptn;
    char pad4[0x18];
    struct IosDC *dc;
    int num;
};
extern char D_kernel_bss_1EAC8[];
struct DCObj *_isysCreateObj(void *parent, int type, int size, int extra, void *arg, int align);
void isysSetObjImmediateDeleteFunc(void *obj, void *fn);
void *iosMallocAlign(void *ptn, int size, int align);
void isysAddGroupWithLinkParam(void *obj, void *group, int a, int b);
void func_00012A98(void);
void func_00012AA0(void);

struct DCObj *iosCreateDC(void *parent, int num) {
    struct DCObj *obj;
    int size = num * sizeof(struct IosDC);

    obj = _isysCreateObj(parent, 0x1F, 0x24, size + 0x33, func_00012A98, 0x10);
    isysSetObjImmediateDeleteFunc(obj, func_00012AA0);
    obj->num = num;
    obj->dc = iosMallocAlign(obj->ptn, size, 0x10);
    obj->dc->owner = obj;
    obj->dc->flags &= ~1;
    obj->dc->flags &= ~2;
    isysAddGroupWithLinkParam(obj, D_kernel_bss_1EAC8, 0, 0);
    return obj;
}
