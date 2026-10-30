/* GAMECORE.XFF @ 0x00C068 (12 B) - getFrameRateMode
 * Shape `ret-addr` recovered by tools/xff_shapes.py and proved by
 * recompiling it byte-exactly (relocations masked).
 * Evidence: `lui $r2` + `jr $ra` + delay `addiu` (HI16/LO16 .data+0x5f8) - returns the object address.
 */
extern char D_kernel_data_05F8[];

int getFrameRateMode(void) {
    return (int)D_kernel_data_05F8;
}
