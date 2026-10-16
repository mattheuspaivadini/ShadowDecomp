/* STATUS (Session 8, 2026-10-14): NON_MATCHING. best score 41 [cc=29].
 * R2 w45a_0: block-layout (&&label placement + saveregs spill)
 * The original .s stays in the build (asm/cod/000C80.s); this C
 * draft (Session 8) is kept for the record. */
extern char D_0013B348[];
extern int eeRegInfo[];

void LoaderSysExecuteRecoveryFirstProcess(void);
void func_0012C048(int *ctx, int fmt, void *ap);
void func_00100A58(void);

void LoaderSysJumpRecoverPoint(int a0, ...) {
    void *resume;
    void *ap;
    int i;
    int *p;

resume_point:
    LoaderSysExecuteRecoveryFirstProcess();
    ap = __builtin_saveregs();
    func_0012C048((int *)D_0013B348, a0, ap);
    resume = &&resume_point;
    p = (int *)((char *)eeRegInfo + 0x1F8);
    for (i = 0x3F; i >= 0; i--) {
        *p = 0;
        p -= 2;
    }
    *(int *)((char *)eeRegInfo + 0x170) = (int)resume;
    *(int *)((char *)eeRegInfo + 0x0F8) = (int)__builtin_return_address(0);
    *(int *)((char *)eeRegInfo + 0x0E8) = (int)__builtin_frame_address(0);
    func_00100A58();
}
