/* GAMECORE.XFF @ 0x015990 (36 B) - tailsFlagsAllClr
 * Evidence: `$a0 = .bss+0x618`, `$a1 = 0`, `$a2 = 0x320`, sibling `j memset`.
 * UNCONFIRMED: the flag block's meaning.
 
 */
extern char D_kernel_bss_0618[];
void memset(void *dst, int value, unsigned int size);

void tailsFlagsAllClr(void) {
    memset(D_kernel_bss_0618, 0, 0x320);
}
