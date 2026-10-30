/* GAMECORE.XFF @ 0x0C5340 (12 B) - getMaxAngle
 * Shape `ret-addr` recovered by tools/xff_shapes.py and proved by
 * recompiling it byte-exactly (relocations masked).
 * Evidence: `lui $r2` + `jr $ra` + delay `addiu` (HI16/LO16 .data+0x1804) - returns the object address.
 */
extern char D_kernel_data_1804[];

int getMaxAngle(void) {
    return (int)D_kernel_data_1804;
}
