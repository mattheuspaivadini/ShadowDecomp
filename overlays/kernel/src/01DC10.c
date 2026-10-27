/* KERNEL.XFF @ 0x01DC10 (12 B) - isysDebugSetSubThreadSleepProtection
 * Shape `store-arg` recovered by tools/xff_shapes.py and proved by
 * recompiling it byte-exactly (relocations masked).
 * Evidence: `lui` + `sw $a0,lo(...)` + `jr $ra` - writes the argument to .data+0xa14.
 */
extern int D_kernel_data_0A14;

void isysDebugSetSubThreadSleepProtection(int a0) {
    D_kernel_data_0A14 = a0;
}
