/* GAMECORE.XFF @ 0x00A820 (12 B) - getSightOnAngleVelRatio
 * Shape `ret-addr` recovered by tools/xff_shapes.py and proved by
 * recompiling it byte-exactly (relocations masked).
 * Evidence: `lui $r2` + `jr $ra` + delay `addiu` (HI16/LO16 .data+0x228) - returns the object address.
 */
extern char D_kernel_data_0228[];

int getSightOnAngleVelRatio(void) {
    return (int)D_kernel_data_0228;
}
