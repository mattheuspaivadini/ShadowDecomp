/* GAMECORE.XFF @ 0x07B548 (12 B) - getPlayerLastAttrStatus
 * Shape `ret-load` recovered by tools/xff_shapes.py and proved by
 * recompiling it byte-exactly (relocations masked).
 * Evidence: `lui` + `jr $ra` + delay `ld $v0,lo(...)` against .data+0x15d0 - returns that object as `unsigned long`.
 */
extern unsigned long D_kernel_data_15D0;

unsigned long getPlayerLastAttrStatus(void) {
    return D_kernel_data_15D0;
}
