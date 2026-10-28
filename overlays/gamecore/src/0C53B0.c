/* GAMECORE.XFF @ 0x0C53B0 (12 B) - getMaxAngleWeak
 * Shape `ret-addr` recovered by tools/xff_shapes.py and proved by
 * recompiling it byte-exactly (relocations masked).
 * Evidence: `lui $r2` + `jr $ra` + delay `addiu` (HI16/LO16 .data+0x1820) - returns the object address.
 */
extern char D_kernel_data_1820[];

int getMaxAngleWeak(void) {
    return (int)D_kernel_data_1820;
}
