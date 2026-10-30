/* GAMECORE.XFF @ 0x0C52F0 (12 B) - getMinAmbient
 * Shape `ret-addr` recovered by tools/xff_shapes.py and proved by
 * recompiling it byte-exactly (relocations masked).
 * Evidence: `lui $r2` + `jr $ra` + delay `addiu` (HI16/LO16 .data+0x17f0) - returns the object address.
 */
extern char D_kernel_data_17F0[];

int getMinAmbient(void) {
    return (int)D_kernel_data_17F0;
}
