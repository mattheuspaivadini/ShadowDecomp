/* GAMECORE.XFF @ 0x0F88A8 (44 B) - getPathInfo
 * Evidence: loads $v1, 0x3C50($a0); relocs <.bss>
 
 */
/* UNCONFIRMED: +0x3C50 indexes the 0x98-byte path info array at .bss+0x21CC8. */
extern char D_kernel_bss_21CC8[];

void *getPathInfo(char *p) {
    return D_kernel_bss_21CC8 + *(int *)(p + 0x3C50) * 0x98;
}
