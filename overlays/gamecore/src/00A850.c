/* GAMECORE.XFF @ 0x00A850 (12 B) - getFreeModeRevAngleVelRatio
 * Shape `ret-addr` recovered by tools/xff_shapes.py and proved by
 * recompiling it byte-exactly (relocations masked).
 * Evidence: `lui $r2` + `jr $ra` + delay `addiu` (HI16/LO16 .data+0x234) - returns the object address.
 */
extern char D_kernel_data_0234[];

int getFreeModeRevAngleVelRatio(void) {
    return (int)D_kernel_data_0234;
}
