/* GAMECORE.XFF @ 0x096C40 (12 B) - getBossCloudObj
 * Shape `ret-load` recovered by tools/xff_shapes.py and proved by
 * recompiling it byte-exactly (relocations masked).
 * Evidence: `lui` + `jr $ra` + delay `lw $v0,lo(...)` against .data+0x16c8 - returns that object as `int`.
 */
extern int D_kernel_data_16C8;

int getBossCloudObj(void) {
    return D_kernel_data_16C8;
}
