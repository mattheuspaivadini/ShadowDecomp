/* KERNEL.XFF @ 0x01DBC0 (68 B) - isysGetSubThreadStackSize
 * Evidence: returns env->size (+0x14). The sub-thread environment is at +0x20 of the object for types 6, 9, 11..14, 22, 29 and 33 and NULL otherwise: an inlined switch helper (jump table at .rodata+0x2620 / +0x2A10, read from the container).
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

int isysGetSubThreadStackSize(struct IsysObj *obj) {
    return getSubThreadEnv(obj)->size;
}
