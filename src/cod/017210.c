/* asm/cod/017210.s -> func_0010FB20.
 * guard + tail call; wave3e (R1)
 * MATCHED (Session 8). */
extern int D_00133A64[];   /* .data 0x00133A64: in-use guard word */
extern int D_00133A88[];   /* .data 0x00133A88: installed flag    */

int  DIntr(void);
int  EIntr(void);
void sceSifAddCmdHandler(int id, int handler, int arg);
void func_001171B8(void);

int func_00117210(void) {
    int one;
    int g;

    one = 1;
    D_00133A64[0] = one;
    g = DIntr();
    sceSifAddCmdHandler(0x80000012, (int)func_001171B8, 0);
    if (g)
        EIntr();
    D_00133A64[0] = 0;
    D_00133A88[0] = one;
    return 1;
}
