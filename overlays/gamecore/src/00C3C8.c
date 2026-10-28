/* GAMECORE.XFF @ 0x00C3C8 (12 B) - getDemoBarSw
 * Shape `ret-addr` recovered by tools/xff_shapes.py and proved by
 * recompiling it byte-exactly (relocations masked).
 * Evidence: `lui $r2` + `jr $ra` + delay `addiu` (HI16/LO16 .data+0x680) - returns the object address.
 */
extern char D_kernel_data_0680[];

int getDemoBarSw(void) {
    return (int)D_kernel_data_0680;
}
