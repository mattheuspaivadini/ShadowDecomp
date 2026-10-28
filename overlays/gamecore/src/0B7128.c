/* GAMECORE.XFF @ 0x0B7128 (12 B) - setSmallManagerSystemLock
 * Shape `store-arg` recovered by tools/xff_shapes.py and proved by
 * recompiling it byte-exactly (relocations masked).
 * Evidence: `lui` + `sw $a0,lo(...)` + `jr $ra` - writes the argument to .bss+0x29120.
 */
extern int D_kernel_bss_29120;

void setSmallManagerSystemLock(int a0) {
    D_kernel_bss_29120 = a0;
}
