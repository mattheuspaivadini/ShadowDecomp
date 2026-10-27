/* KERNEL.XFF @ 0x01B6D0 (12 B) - GetGarbageTime
 * Shape `ret-load` recovered by tools/xff_shapes.py and proved by
 * recompiling it byte-exactly (relocations masked).
 * Evidence: `lui` + `jr $ra` + delay `ld $v0,lo(...)` against .bss+0x89198 - returns that object as `unsigned long`.
 */
extern unsigned long D_kernel_bss_89198;

unsigned long GetGarbageTime(void) {
    return D_kernel_bss_89198;
}
