/* KERNEL.XFF @ 0x0257F0 (12 B) - Sg2RemoteGetPcmStmTransOffset
 * Shape `ret-load` recovered by tools/xff_shapes.py and proved by
 * recompiling it byte-exactly (relocations masked).
 * Evidence: `lui` + `jr $ra` + delay `lw $v0,lo(...)` against .bss+0x96ec0 - returns that object as `int`.
 */
extern int D_kernel_bss_96EC0;

int Sg2RemoteGetPcmStmTransOffset(void) {
    return D_kernel_bss_96EC0;
}
