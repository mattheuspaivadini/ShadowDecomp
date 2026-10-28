/* KERNEL.XFF @ 0x004BF8 (136 B) - func_004BF8 (static, no symbol in the shipped .symtab)
 * Evidence: for the 0x44-byte network record [i] at .bss+0xA370 (cid +0, buffer +4, libnet client data +8): sceInetClose(cd, buf, cid, ms); cid = -1; sceLibnetTerminate(cd); iosFree(buf); buf = 0; returns 1. UNCONFIRMED: names; Ghidra FUN_00204bf8.
 */
struct NetRec {
    int cid;
    unsigned int *buf;
    char cd[0x44 - 8];
};
extern struct NetRec D_kernel_bss_0A370[];
int sceInetClose(void *cd, unsigned int *buf, int cid, int ms);
int sceLibnetTerminate(void *cd);
void iosFree(void *p);

int func_004BF8(int i, int ms) {
    sceInetClose(D_kernel_bss_0A370[i].cd, D_kernel_bss_0A370[i].buf, D_kernel_bss_0A370[i].cid, ms);
    D_kernel_bss_0A370[i].cid = -1;
    sceLibnetTerminate(D_kernel_bss_0A370[i].cd);
    iosFree(D_kernel_bss_0A370[i].buf);
    D_kernel_bss_0A370[i].buf = 0;
    return 1;
}
