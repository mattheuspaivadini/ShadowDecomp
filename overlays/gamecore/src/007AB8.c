/* GAMECORE.XFF @ 0x007AB8 (12 B) - getSnapShotFormat
 * Shape `ret-addr` recovered by tools/xff_shapes.py and proved by
 * recompiling it byte-exactly (relocations masked).
 * Evidence: `lui $r2` + `jr $ra` + delay `addiu` (HI16/LO16 .data+0x5c) - returns the object address.
 */
extern char D_kernel_data_005C[];

int getSnapShotFormat(void) {
    return (int)D_kernel_data_005C;
}
