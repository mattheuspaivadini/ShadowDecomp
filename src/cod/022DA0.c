/* asm/cod/022DA0.s -> func_00122DA0 @ 0x00122DA0
 * func_001221D0(); store a0 into D_00167F00; then
 * func_00123260(D_00167EC0, D_00167F00, 0x65). */
int func_001221D0(void);
int func_00123260(char *dst, char *src, int n);

extern char D_00167EC0[];
extern int D_00167F00[];

int func_00122DA0(int a0) {
    func_001221D0();
    D_00167F00[0] = a0;
    return func_00123260(D_00167EC0, (char *)D_00167F00, 0x65);
}
