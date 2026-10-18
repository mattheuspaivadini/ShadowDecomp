/* asm/cod/0232F0.s -> sce_sync.
 * sce_sync; switch(mode) + volatile sema id (Session 23)
 * MATCHED. */
extern volatile int D_00135960[];
int WaitSema(int s);
int PollSema(int s);
int func_00123208(void);

int sce_sync(int mode) {
    int r = 1;
    if (D_00135960[0] < 0) return -1;
    switch (mode) {
    case 0:
        WaitSema(D_00135960[0]);
        func_00123208();
        r = 0;
        break;
    case 1:
        if (PollSema(D_00135960[0]) != -1) {
            func_00123208();
            r = 0;
        }
        break;
    default:
        return -0x65;
    }
    return r;
}
