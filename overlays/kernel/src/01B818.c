/* KERNEL.XFF @ 0x01B818 (164 B) - func_01B818 (static, no symbol in the shipped .symtab)
 * STATUS: MATCHING [-G0 -fno-strict-aliasing]
 * Evidence: returns 1 when .data+0x7DC is set, else 1 only if the argument equals
 * .data+0x7D4 and (float)(iosGetTCountExtension() - .bss+0x79190) < 0x4A01B31F
 * (unsigned DI->SF conversion via __floatdisf); 0 otherwise. The .data+0x7D4 read
 * is a lui/addiu/lw 0 => volatile. Ghidra FUN_0021b818.
 * Lever: `goto ok` into the shared `ret = 1` places `ret = 0` after the first test.
 * Levers tried: || chain (6/41), early returns (14/41), else ret = 0 (size).
 * UNCONFIRMED: name, argument meaning, global meanings.
 */
unsigned long iosGetTCountExtension(void);
extern int D_kernel_data_07DC;
extern volatile int D_kernel_data_07D4;
extern unsigned long D_kernel_bss_79190;

int func_01B818(int id) {
    int ret;
    if (D_kernel_data_07DC != 0) goto ok;
    ret = 0;
    if (id == D_kernel_data_07D4 && (float)(iosGetTCountExtension() - D_kernel_bss_79190) < 2124999.75f) {
ok:     ret = 1;
    }
    return ret;
}
