/* GAMECORE.XFF @ 0x02DD10 (12 B) - getBossExtControl
 * Shape `ret-addr` recovered by tools/xff_shapes.py and proved by
 * recompiling it byte-exactly (relocations masked).
 * Evidence: `lui $r2` + `jr $ra` + delay `addiu` (HI16/LO16 .data+0x1070) - returns the object address.
 */
extern char D_kernel_data_1070[];

int getBossExtControl(void) {
    return (int)D_kernel_data_1070;
}
