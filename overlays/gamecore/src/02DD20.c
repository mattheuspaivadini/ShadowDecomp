/* GAMECORE.XFF @ 0x02DD20 (12 B) - getTargetAIControlMode
 * Shape `ret-addr` recovered by tools/xff_shapes.py and proved by
 * recompiling it byte-exactly (relocations masked).
 * Evidence: `lui $r2` + `jr $ra` + delay `addiu` (HI16/LO16 .data+0x1074) - returns the object address.
 */
extern char D_kernel_data_1074[];

int getTargetAIControlMode(void) {
    return (int)D_kernel_data_1074;
}
