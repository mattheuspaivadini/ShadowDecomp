/* GAMECORE.XFF @ 0x04C468 (12 B) - getPendulumGravityRatio
 * Shape `ret-addr` recovered by tools/xff_shapes.py and proved by
 * recompiling it byte-exactly (relocations masked).
 * Evidence: `lui $r2` + `jr $ra` + delay `addiu` (HI16/LO16 .data+0x1108) - returns the object address.
 */
extern char D_kernel_data_1108[];

int getPendulumGravityRatio(void) {
    return (int)D_kernel_data_1108;
}
