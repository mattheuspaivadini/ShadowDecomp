/* GAMECORE.XFF @ 0x007DA0 (12 B) - getDispGpsMarker
 * Shape `ret-addr` recovered by tools/xff_shapes.py and proved by
 * recompiling it byte-exactly (relocations masked).
 * Evidence: `lui $r2` + `jr $ra` + delay `addiu` (HI16/LO16 .data+0x1a8) - returns the object address.
 */
extern char D_kernel_data_01A8[];

int getDispGpsMarker(void) {
    return (int)D_kernel_data_01A8;
}
