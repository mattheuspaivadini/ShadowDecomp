/* KERNEL.XFF @ 0x01D8F8 (252 B) - isysCreateSubThreadS
 * Evidence: _isysCreateObj(parent, 3, 0x40, size + 0x10, .text+0x1CF90, 4) followed by an inlined copy of isysInitSubThreadObj(obj, entry, 0, size) (static inline copy of 01D828); returns the object when that succeeded, else NULL. UNCONFIRMED: names.
 */
struct SubThreadEnv {
    void *cur;
    void *top;
    int unk8;
    char *stack;
    char *sp;
    int size;
    int unk18;
};
struct IsysObj {
    void *ptn;
    char pad4[4];
    unsigned char type;
    char pad9[0x17];
    struct SubThreadEnv env;
};
extern char D_kernel_data_0A18[];
void *iosMallocAlign(void *ptn, int size, int align);
void isysAddGroupWithLinkParam(void *obj, void *group, int a, int b);

static __inline__ struct SubThreadEnv *getSubThreadEnv(struct IsysObj *obj) {
    switch (obj->type) {
    case 6:
    case 9:
    case 11:
    case 12:
    case 13:
    case 14:
    case 22:
    case 29:
    case 33:
        return &obj->env;
    }
    return 0;
}

static __inline__ int isysInitSubThreadObj(struct IsysObj *obj, void *entry, int unused, int size) {
    struct SubThreadEnv *env = getSubThreadEnv(obj);

    env->stack = iosMallocAlign(obj->ptn, size, 0x10);
    if (env->stack == 0) {
        return -1;
    }
    env->sp = env->stack + size;
    env->cur = entry;
    env->top = entry;
    env->size = size;
    env->unk18 = 1;
    isysAddGroupWithLinkParam(obj, D_kernel_data_0A18, 0, 0);
    return 0;
}
struct IsysObj *_isysCreateObj(void *parent, int type, int size, int extra, void *func, int align);
void func_0001CF90(void);

struct IsysObj *isysCreateSubThreadS(void *entry, void *parent, int size) {
    struct IsysObj *obj;

    obj = _isysCreateObj(parent, 3, 0x40, size + 0x10, func_0001CF90, 4);
    if (obj == 0) {
        return 0;
    }
    return isysInitSubThreadObj(obj, entry, 0, size) == 0 ? obj : 0;
}
