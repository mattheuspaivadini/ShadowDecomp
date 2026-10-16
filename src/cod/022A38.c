/* asm/cod/022A38.s -> func_001221D0.
 * empty-asm register pin on strcpy return value
 * MATCHED (Session 8). */
#include "symbols.h"

int func_001221D0(void);
char *func_00128FB0(char *dst, char *src);
int func_00123260(char *dst, char *src, int n);

extern char D_00167F00[];
extern char D_00167EC0[];

int func_00122A38(int a0, int a1, int a2, int a3) {
    int off_a = 0x10;
    int off_b = 0x110;
    int off_c = 0x210;
    char *ret;

    func_001221D0();
    func_00128FB0(D_00167F00 + off_a, (char *)a0);
    *(int *)(D_00167F00 + 8) = a1;
    func_00128FB0(D_00167F00 + off_b, (char *)a2);
    ret = func_00128FB0(D_00167F00 + off_c, (char *)a3);
    asm volatile ("" : "+r" (ret));
    *(int *)(D_00167F00 + 4) = D_00135958;
    return func_00123260(D_00167EC0, D_00167F00, 4);
}