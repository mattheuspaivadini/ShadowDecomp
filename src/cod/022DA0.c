/* asm/cod/022DA0.s -> func_00122DA0 @ 0x00122DA0
 * func_001221D0(); store a0 into D_00167F00; then
 * func_00123260(D_00167EC0, D_00167F00, 0x65). */
int sceNetcnfifInit(void);
int sce_call_rpc(char *dst, char *src, int n);

extern char D_00167EC0[];
extern int D_00167F00[];

int sceNetcnfifAllocWorkarea(int a0) {
    sceNetcnfifInit();
    D_00167F00[0] = a0;
    return sce_call_rpc(D_00167EC0, (char *)D_00167F00, 0x65);
}
