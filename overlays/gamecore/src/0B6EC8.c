/* GAMECORE.XFF @ 0x0B6EC8 (48 B) - terminateSmallManager
 * Evidence: stores $s0, 0x0($sp), $ra, 0x8($sp); loads $ra, 0x8($sp), $s0, 0x0($sp); relocs <.bss>; calls <.text>, j <.text>; frame
 
 */
void func_000B72E0(char *p);
extern char D_kernel_bss_7D50[];

void terminateSmallManager(void) {
    func_000B72E0(D_kernel_bss_7D50);
    func_000B72E0(D_kernel_bss_7D50 + 0x9E0);
}
