/* GAMECORE.XFF @ 0x007900 (12 B) - getCollisionDispMode
 * Shape `ret-addr` recovered by tools/xff_shapes.py and proved by
 * recompiling it byte-exactly (relocations masked).
 * Evidence: `lui $r2` + `jr $ra` + delay `addiu` (HI16/LO16 .data+0x1c) - returns the object address.
 */
extern char D_kernel_data_001C[];

int getCollisionDispMode(void) {
    return (int)D_kernel_data_001C;
}
