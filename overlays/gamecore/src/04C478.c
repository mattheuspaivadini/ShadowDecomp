/* GAMECORE.XFF @ 0x04C478 (12 B) - getPendulumAirResistRatio
 * Shape `ret-addr` recovered by tools/xff_shapes.py and proved by
 * recompiling it byte-exactly (relocations masked).
 * Evidence: `lui $r2` + `jr $ra` + delay `addiu` (HI16/LO16 .data+0x110c) - returns the object address.
 */
extern char D_kernel_data_110C[];

int getPendulumAirResistRatio(void) {
    return (int)D_kernel_data_110C;
}
