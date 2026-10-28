/* GAMECORE.XFF @ 0x0C5310 (12 B) - getMinAmbientLine
 * Shape `ret-addr` recovered by tools/xff_shapes.py and proved by
 * recompiling it byte-exactly (relocations masked).
 * Evidence: `lui $r2` + `jr $ra` + delay `addiu` (HI16/LO16 .data+0x17f8) - returns the object address.
 */
extern char D_kernel_data_17F8[];

int getMinAmbientLine(void) {
    return (int)D_kernel_data_17F8;
}
