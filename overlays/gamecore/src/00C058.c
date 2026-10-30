/* GAMECORE.XFF @ 0x00C058 (12 B) - getDummyCount
 * Shape `ret-load` recovered by tools/xff_shapes.py and proved by
 * recompiling it byte-exactly (relocations masked).
 * Evidence: `lui` + `jr $ra` + delay `ld $v0,lo(...)` against .data+0x600 - returns that object as `unsigned long`.
 */
extern unsigned long D_kernel_data_0600;

unsigned long getDummyCount(void) {
    return D_kernel_data_0600;
}
