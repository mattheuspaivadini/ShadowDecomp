/* GAMECORE.XFF @ 0x015F70 (40 B) - optionFlagInit
 * Evidence: `memset(.bss+0x348, 0, 0x88)` then a sibling `j` to
 * `optionMenuParamSetDefault` (no arguments).
 * UNCONFIRMED: the block meaning and the callee prototype.
 
 */
extern char D_kernel_bss_0348[];
void memset(void *dst, int value, unsigned int size);
void optionMenuParamSetDefault(void);

void optionFlagInit(void) {
    memset(D_kernel_bss_0348, 0, 0x88);
    optionMenuParamSetDefault();
}
