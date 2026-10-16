/* asm/cod/022D68.s -> func_00122D68 @ 0x00122D68
 * func_001221D0(); then func_00123260(D_00167EC0, D_00167F00, 0x64) whose
 * result is returned. */
int sceNetcnfifInit(void);
int sce_call_rpc(char *dst, char *src, int n);

extern char D_00167EC0[];
extern char D_00167F00[];

int sceNetcnfifGetAddr(void) {
    sceNetcnfifInit();
    return sce_call_rpc(D_00167EC0, D_00167F00, 0x64);
}
