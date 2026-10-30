/* GAMECORE.XFF @ 0x0D0FD8 (12 B) - getSprLogWorkAddress
 * Shape `ret-addr` recovered by tools/xff_shapes.py and proved by
 * recompiling it byte-exactly (relocations masked).
 * Evidence: `lui $r2` + `jr $ra` + delay `addiu` (HI16/LO16 .bss+0x29430) - returns the object address.
 */
extern char D_kernel_bss_29430[];

int getSprLogWorkAddress(void) {
    return (int)D_kernel_bss_29430;
}
