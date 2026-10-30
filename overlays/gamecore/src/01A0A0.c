/* GAMECORE.XFF @ 0x01A0A0 (12 B) - gstatBootMcChkExistIcoData
 * Shape `ret-load` recovered by tools/xff_shapes.py and proved by
 * recompiling it byte-exactly (relocations masked).
 * Evidence: `lui` + `jr $ra` + delay `lw $v0,lo(...)` against .data+0x9f0 - returns that object as `int`.
 */
extern int D_kernel_data_09F0;

int gstatBootMcChkExistIcoData(void) {
    return D_kernel_data_09F0;
}
