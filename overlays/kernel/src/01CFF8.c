/* KERNEL.XFF @ 0x01CFF8 (176 B) - isysDumpSubThreadStatus
 * Evidence: inlined sub-thread env switch (jump table .rodata+0x2770: types 6, 9, 11..14, 22, 29, 33); two 0x100-byte rootPtn buffers (iosMallocAlign align 4), isysSearchModuleFuncNameByAddr(module, func, env->cur), both freed (second iosFree as a tail call). The dump printf itself is compiled out. UNCONFIRMED: buffer roles.
 */
struct SubThreadEnv {
    void *cur;
    void *top;
    int unk8;
    char *stack;
    char *sp;
    int size;
};
struct IsysObj {
    char pad[8];
    unsigned char type;
    char pad2[0x17];
    struct SubThreadEnv env;
};
extern char rootPtn[];
void *iosMallocAlign(void *ptn, int size, int align);
void iosFree(void *p);
void isysSearchModuleFuncNameByAddr(char *module, char *func, void *addr);

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

void isysDumpSubThreadStatus(struct IsysObj *obj) {
    struct SubThreadEnv *env = getSubThreadEnv(obj);
    char *module = iosMallocAlign(rootPtn, 0x100, 4);
    char *func = iosMallocAlign(rootPtn, 0x100, 4);

    isysSearchModuleFuncNameByAddr(module, func, env->cur);
    iosFree(func);
    iosFree(module);
}
