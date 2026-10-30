/* GAMECORE.XFF @ 0x0C5300 (12 B) - getMaxAmbient
 * Shape `ret-addr` recovered by tools/xff_shapes.py and proved by
 * recompiling it byte-exactly (relocations masked).
 * Evidence: `lui $r2` + `jr $ra` + delay `addiu` (HI16/LO16 .data+0x17f4) - returns the object address.
 */
extern char D_kernel_data_17F4[];

int getMaxAmbient(void) {
    return (int)D_kernel_data_17F4;
}
