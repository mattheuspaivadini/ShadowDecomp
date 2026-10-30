/* GAMECORE.XFF @ 0x015F98 (20 B) - getOptionDataAdrsAndSize
 * Evidence: *a0 = 0x88; return bss+0x348
 * UNCONFIRMED: none
 */
extern char D_kernel_bss_0348[];

char *getOptionDataAdrsAndSize(int *size) {
    *size = 0x88;
    return D_kernel_bss_0348;
}
