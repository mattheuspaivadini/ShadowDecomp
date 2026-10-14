/* asm/cod/022BD8.s -> func_001221D0 (cc=29).
 * 022DA0 idiom (int wrapper, `return func_00123260(...)`) + the `+0x10` offset as a named local (const-local pattern). Command 7.
 * MATCHED (Session 7). */
/* v10: mirror the matched 022DA0 (int wrapper, `return` the command call). */
int func_001221D0(void);
void func_00128FB0(char *dst, char *src);
int func_00123260(char *dst, char *src, int n);

extern char D_00167F00[];
extern char D_00167EC0[];

int func_00122BD8(int a0) {int lit_0 = 0x10;

    func_001221D0();
    func_00128FB0(D_00167F00 + lit_0, (char *)a0);
    return func_00123260(D_00167EC0, D_00167F00, 7);
}
