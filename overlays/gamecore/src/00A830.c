/* GAMECORE.XFF @ 0x00A830 (12 B) - getFreeModeRevControlLR
 * Shape `ret-addr` recovered by tools/xff_shapes.py and proved by
 * recompiling it byte-exactly (relocations masked).
 * Evidence: `lui $r2` + `jr $ra` + delay `addiu` (HI16/LO16 .data+0x22c) - returns the object address.
 */
extern char D_kernel_data_022C[];

int getFreeModeRevControlLR(void) {
    return (int)D_kernel_data_022C;
}
