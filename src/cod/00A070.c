/* asm/cod/00A070.s -> func_00109E50.
 * session9 step1 residue: nested drain-loop form
 * MATCHED (Session 8). */
int *func_00109E50(int *ctx);
void func_00109EA8(int *node);
void func_00106F00(void);

void func_0010A070(int *ctx) {
    int *node;
    int *c;

    c = ctx;
    for (;;) {
        while ((node = func_00109E50(c)) != 0)
            func_00109EA8(node);
        func_00106F00();
    }
}
