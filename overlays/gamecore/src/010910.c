/* GAMECORE.XFF @ 0x010910 (12 B) - CheckCamFinalizerReady
 * Shape `ret-load` recovered by tools/xff_shapes.py and proved by
 * recompiling it byte-exactly (relocations masked).
 * Evidence: `lui` + `jr $ra` + delay `lw $v0,lo(...)` against .data+0x6f0 - returns that object as `int`.
 */
extern int D_kernel_data_06F0;

int CheckCamFinalizerReady(void) {
    return D_kernel_data_06F0;
}
