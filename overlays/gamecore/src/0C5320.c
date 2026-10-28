/* GAMECORE.XFF @ 0x0C5320 (12 B) - getMaxAmbientLine
 * Shape `ret-addr` recovered by tools/xff_shapes.py and proved by
 * recompiling it byte-exactly (relocations masked).
 * Evidence: `lui $r2` + `jr $ra` + delay `addiu` (HI16/LO16 .data+0x17fc) - returns the object address.
 */
extern char D_kernel_data_17FC[];

int getMaxAmbientLine(void) {
    return (int)D_kernel_data_17FC;
}
