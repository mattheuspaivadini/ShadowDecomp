/* asm/cod/023000.s -> sce_create_callback_thread.
 * callback-thread create; ThreadParam struct, $gp via volatile asm move (Session 22)
 * MATCHED. */
struct ThreadParam {
    int status;             /* 0x00 */
    void *func;             /* 0x04 */
    void *stack;            /* 0x08 */
    int stackSize;          /* 0x0C */
    void *gpReg;            /* 0x10 */
    int initPriority;       /* 0x14 */
    int currentPriority;    /* 0x18 */
    unsigned int attr;      /* 0x1C */
    unsigned int option;    /* 0x20 */
    int pad[3];
};
struct B23000 { unsigned int w[4]; };

int CreateThread(struct ThreadParam *param);
int StartThread(int thread, void *arg);
int DeleteThread(int thread);
void func_00122F90(void);

extern char D_00138DD0[];
extern struct B23000 D_00169F00;

int sce_create_callback_thread(struct B23000 *a0, void *stack, int size, int prio) {
    struct ThreadParam tp;
    void *gp;
    int id;

    tp.func = func_00122F90;
    tp.stack = stack;
    tp.stackSize = size;
    tp.initPriority = prio;
    __asm__ volatile ("move %0, $gp" : "=r"(gp));
    tp.gpReg = gp;
    tp.option = (unsigned int)D_00138DD0;
    id = CreateThread(&tp);
    if (id <= 0)
        return -1;
    D_00169F00 = *a0;
    if (StartThread(id, 0) >= 0)
        return id;
    DeleteThread(id);
    return -1;
}
