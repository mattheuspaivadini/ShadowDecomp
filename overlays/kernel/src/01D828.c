/* KERNEL.XFF @ 0x01D828 (208 B) - isysInitSubThreadObj
 * Evidence: inlined sub-thread env switch (jump table .rodata+0x2850); stack = iosMallocAlign(obj partition +0, size, 0x10), -1 when NULL; sp = stack + size, +0x18 = 1, entry into top and cur, size kept; isysAddGroupWithLinkParam(obj, .data+0xA18, 0, 0); returns 0. Third argument unused. UNCONFIRMED: field names.
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

int isysInitSubThreadObj(struct IsysObj *obj, void *entry, int unused, int size) {
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
