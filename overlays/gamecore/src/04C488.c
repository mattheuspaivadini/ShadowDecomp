/* GAMECORE.XFF @ 0x04C488 (12 B) - getPendulumSideFriction
 * Shape `ret-addr` recovered by tools/xff_shapes.py and proved by
 * recompiling it byte-exactly (relocations masked).
 * Evidence: `lui $r2` + `jr $ra` + delay `addiu` (HI16/LO16 .data+0x1110) - returns the object address.
 */
extern char D_kernel_data_1110[];

int getPendulumSideFriction(void) {
    return (int)D_kernel_data_1110;
}
