/* asm/cod/010120.s -> ExecPS2.
 * ExecPS2 cc=29
 * MATCHED (Session 12). */
extern int D_00138270[];
extern int _kExecArg[];

int func_00110000(int *p, int a0, int a1);
void func_00110118(void);
int _ExecPS2(int a0, int a1, int a2, int a3);

int ExecPS2(int a0, int a1, int a2, int a3) {
    func_00110000(D_00138270, a2, a3);
    func_00110118();
    return _ExecPS2(a0, a1, a2, _kExecArg[0] + 4);
}
