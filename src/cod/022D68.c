/* asm/cod/022D68.s -> func_00122D68 @ 0x00122D68
 * func_001221D0(); then func_00123260(D_00167EC0, D_00167F00, 0x64) whose
 * result is returned. */
int func_001221D0(void);
int func_00123260(char *dst, char *src, int n);

extern char D_00167EC0[];
extern char D_00167F00[];

int func_00122D68(void) {
    func_001221D0();
    return func_00123260(D_00167EC0, D_00167F00, 0x64);
}
