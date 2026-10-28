/* GAMECORE.XFF @ 0x04E830 (12 B) - getWeakGlowTime
 * Shape `ret-addr` recovered by tools/xff_shapes.py and proved by
 * recompiling it byte-exactly (relocations masked).
 * Evidence: `lui $r2` + `jr $ra` + delay `addiu` (HI16/LO16 .data+0x12f8) - returns the object address.
 */
extern char D_kernel_data_12F8[];

int getWeakGlowTime(void) {
    return (int)D_kernel_data_12F8;
}
