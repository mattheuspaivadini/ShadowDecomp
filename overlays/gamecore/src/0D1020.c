/* GAMECORE.XFF @ 0x0D1020 (12 B) - getLogLineColorB
 * Shape `ret-addr` recovered by tools/xff_shapes.py and proved by
 * recompiling it byte-exactly (relocations masked).
 * Evidence: `lui $r2` + `jr $ra` + delay `addiu` (HI16/LO16 .data+0x1ad8) - returns the object address.
 */
extern char D_kernel_data_1AD8[];

int getLogLineColorB(void) {
    return (int)D_kernel_data_1AD8;
}
