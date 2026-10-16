/* asm/cod/022B58.s -> func_001221D0.
 * session9 R1 w25b command family c6
 * MATCHED (Session 8). */
#include "symbols.h"

int sceNetcnfifInit(void);
void func_00128FB0(char *dst, char *src);
int sce_call_rpc(char *dst, char *src, int n);

extern char D_00167F00[];
extern char D_00167EC0[];

int sceNetcnfifSetLatestEntry(int a0, int a1, int a2) {
    int off_a = 0x10;
    int off_b = 0x110;

    sceNetcnfifInit();
    func_00128FB0(D_00167F00 + off_a, (char *)a0);
    *(int *)(D_00167F00 + 8) = a1;
    func_00128FB0(D_00167F00 + off_b, (char *)a2);
    return sce_call_rpc(D_00167EC0, D_00167F00, 6);
}
