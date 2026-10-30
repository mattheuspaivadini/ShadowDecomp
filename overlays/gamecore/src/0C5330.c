/* GAMECORE.XFF @ 0x0C5330 (12 B) - getMinAngle
 * Shape `ret-addr` recovered by tools/xff_shapes.py and proved by
 * recompiling it byte-exactly (relocations masked).
 * Evidence: `lui $r2` + `jr $ra` + delay `addiu` (HI16/LO16 .data+0x1800) - returns the object address.
 */
extern char D_kernel_data_1800[];

int getMinAngle(void) {
    return (int)D_kernel_data_1800;
}
