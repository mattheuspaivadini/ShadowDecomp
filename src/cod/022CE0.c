/* asm/cod/022CE0.s -> func_001221D0.
 * empty-asm register pin on strcpy return value
 * MATCHED (Session 8). */
#include "symbols.h"

int sceNetcnfifInit(void);
char *func_00128FB0(char *dst, char *src);
int sce_call_rpc(char *dst, char *src, int n);

extern char D_00167F00[];
extern char D_00167EC0[];

int sceNetcnfifCheckSpecialProvider(int a0, int a1, int a2) {
    int off_a = 0x10;
    int off_b = 0x110;
    char *ret;

    sceNetcnfifInit();
    func_00128FB0(D_00167F00 + off_a, (char *)a0);
    *(int *)(D_00167F00 + 8) = a1;
    ret = func_00128FB0(D_00167F00 + off_b, (char *)a2);
    asm volatile ("" : "+r" (ret));
    *(int *)(D_00167F00 + 4) = D_00135958;
    return sce_call_rpc(D_00167EC0, D_00167F00, 0xA);
}