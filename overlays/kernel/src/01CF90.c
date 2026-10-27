/* KERNEL.XFF @ 0x01CF90 (104 B) - isysDeleteSubThread
 * Evidence: frees env->stack (+0xC) when env->+0x18 is set; env is the inlined sub-thread environment switch (jump table at .rodata+0x2700).
 */
struct SubThreadEnv {
    void *cur;
    void *top;
    int unk8;
    char *stack;
    char *sp;
    int size;
    int allocated;
};
struct IsysObj {
    char pad[8];
    unsigned char type;
    char pad2[0x17];
    struct SubThreadEnv env;
};
void iosFree(void *p);

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

void isysDeleteSubThread(struct IsysObj *obj) {
    struct SubThreadEnv *env = getSubThreadEnv(obj);

    if (env->allocated) {
        iosFree(env->stack);
    }
}
