/* KERNEL.XFF @ 0x01B690 (12 B) - iosSetISchedulerSubthreadTask
 * Shape `store-arg` recovered by tools/xff_shapes.py and proved by
 * recompiling it byte-exactly (relocations masked).
 * Evidence: `lui` + `sw $a0,lo(...)` + `jr $ra` - writes the argument to .data+0x7f4.
 */
extern int D_kernel_data_07F4;

void iosSetISchedulerSubthreadTask(int a0) {
    D_kernel_data_07F4 = a0;
}
