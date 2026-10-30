/* GAMECORE.XFF @ 0x02CCF8 (12 B) - stagemanager_getSegmentVariation
 * Shape `ret-load` recovered by tools/xff_shapes.py and proved by
 * recompiling it byte-exactly (relocations masked).
 * Evidence: `lui` + `jr $ra` + delay `lw $v0,lo(...)` against .data+0xfcc - returns that object as `int`.
 */
extern int D_kernel_data_0FCC;

int stagemanager_getSegmentVariation(void) {
    return D_kernel_data_0FCC;
}
