/* GAMECORE.XFF @ 0x007940 (12 B) - getGripCalcCancelMode
 * Shape `ret-addr` recovered by tools/xff_shapes.py and proved by
 * recompiling it byte-exactly (relocations masked).
 * Evidence: `lui $r2` + `jr $ra` + delay `addiu` (HI16/LO16 .data+0x2c) - returns the object address.
 */
extern char D_kernel_data_002C[];

int getGripCalcCancelMode(void) {
    return (int)D_kernel_data_002C;
}
