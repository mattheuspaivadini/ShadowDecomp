/* asm/cod/00E338.s -> func_00128188.
 * introduce local pointer temporaries in evaluation order
 * MATCHED (Session 8). */
extern char D_0013227C[];
extern char D_001475A8[];
extern int  D_00132334[];

int func_00128188(unsigned int a0, unsigned int a1, unsigned int n);

int func_0010E338(void) {
    char *p1 = D_0013227C;
    char *p2 = D_001475A8;
    int r = 0;

    if (func_00128188((unsigned int)p2, (unsigned int)p1, 4) != 0) {
        if (func_00128188((unsigned int)p2, (unsigned int)D_00132334[0], 4) != 0) {
            r = func_00128188((unsigned int)p1, (unsigned int)D_00132334[0], 4) != 0;
        }
    }
    return r;
}