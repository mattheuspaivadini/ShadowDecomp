/* GAMECORE.XFF @ 0x015D80 (32 B) - gOptionMcSave
 * Evidence: a1=bss+0x348, a2=0x88, sibling j mcWrite
 * UNCONFIRMED: none
 */
extern char D_kernel_bss_0348[];
int mcWrite(int a, char *p, int n);

int gOptionMcSave(int a) {
    return mcWrite(a, D_kernel_bss_0348, 0x88);
}
