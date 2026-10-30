/* GAMECORE.XFF @ 0x121268 (36 B) - scrDemoInit
 * Evidence: stores $ra, 0x0($sp); loads $ra, 0x0($sp); relocs <.bss>; calls j memset; frame
 
 */
void *memset(void *, int, unsigned int);
extern char D_kernel_bss_21F58[];

void scrDemoInit(void) {
    memset(D_kernel_bss_21F58, 0, 0xB0);
}
