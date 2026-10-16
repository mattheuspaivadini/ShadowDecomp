/* asm/cod/022550.s -> func_001221D0.
 * empty-asm register pin on strcpy return value
 * MATCHED (Session 8). */
int sceNetcnfifInit(void);
char *func_00128FB0(char *dst, char *src);
int sce_call_rpc(char *dst, char *src, int n);
extern char D_00167F00[];
extern char D_00167EC0[];
extern int D_00135958[];

int sceNetcnfifLoadEntry(int a0, int a1, int a2, int a3) {
    int lit_0 = 0x10;
    int lit_1 = 0x110;
    char *ret;

    sceNetcnfifInit();
    func_00128FB0(D_00167F00 + lit_0, (char *)a0);
    *(int *)(D_00167F00 + 8) = a1;
    ret = func_00128FB0(D_00167F00 + lit_1, (char *)a2);
    asm volatile ("" : "+r" (ret));
    *(int *)(D_00167F00 + 0xC) = a3;
    *(int *)(D_00167F00 + 4) = D_00135958[0];
    return sce_call_rpc(D_00167EC0, D_00167F00, 2);
}