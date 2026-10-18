/* asm/cod/016E58.s -> sceCdInitEeCB.
 * ret = 1 initialised at the declaration and ret = 0 written after ChangeThreadPriority (Session 28).
 * MATCHED. */
struct ThreadParam {
    int status;
    void *func;
    void *stack;
    int stack_size;
    void *gp_reg;
    int initial_priority;
    int current_priority;
    unsigned int attr;
    unsigned int option;
};

extern __attribute__((section(".data"))) int D_00133A54;
extern struct ThreadParam D_00150E18;
extern char D_00138890[];

void _sceCd_cbLoop(void);
int CreateThread(struct ThreadParam *p);
int StartThread(int thid, void *arg);
int ChangeThreadPriority(int thid, int prio);

int sceCdInitEeCB(int prio, void *stack, int stack_size) {
    int ret = 1;

    if (D_00133A54 == 0) {
        D_00150E18.stack_size = stack_size;
        D_00150E18.func = _sceCd_cbLoop;
        D_00150E18.stack = stack;
        D_00150E18.initial_priority = prio;
        D_00150E18.option = (unsigned int)D_00138890;
        D_00150E18.gp_reg = 0;
        D_00133A54 = CreateThread(&D_00150E18);
        StartThread(D_00133A54, 0);
    } else {
        ChangeThreadPriority(D_00133A54, prio);
        ret = 0;
    }
    return ret;
}
