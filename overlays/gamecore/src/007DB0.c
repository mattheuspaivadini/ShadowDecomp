/* GAMECORE.XFF @ 0x007DB0 (12 B) - getGpsGridWidth
 * Shape `ret-addr` recovered by tools/xff_shapes.py and proved by
 * recompiling it byte-exactly (relocations masked).
 * Evidence: `lui $r2` + `jr $ra` + delay `addiu` (HI16/LO16 .data+0x1ac) - returns the object address.
 */
extern char D_kernel_data_01AC[];

int getGpsGridWidth(void) {
    return (int)D_kernel_data_01AC;
}
