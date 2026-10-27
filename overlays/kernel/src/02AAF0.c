/* KERNEL.XFF @ 0x02AAF0 (12 B) - Sg2SlotGetVolShiftDownParam
 * Shape `ret-load` recovered by tools/xff_shapes.py and proved by
 * recompiling it byte-exactly (relocations masked).
 * Evidence: `lui` + `jr $ra` + delay `lw $v0,lo(...)` against .bss+0x97e2c - returns that object as `int`.
 */
extern int D_kernel_bss_97E2C;

int Sg2SlotGetVolShiftDownParam(void) {
    return D_kernel_bss_97E2C;
}
