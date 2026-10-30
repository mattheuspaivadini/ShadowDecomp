/* GAMECORE.XFF @ 0x0C52E0 (12 B) - GetSwordFlareHitPlaneAttribute
 * Shape `ret-load` recovered by tools/xff_shapes.py and proved by
 * recompiling it byte-exactly (relocations masked).
 * Evidence: `lui` + `jr $ra` + delay `ld $v0,lo(...)` against .data+0x1888 - returns that object as `unsigned long`.
 */
extern unsigned long D_kernel_data_1888;

unsigned long GetSwordFlareHitPlaneAttribute(void) {
    return D_kernel_data_1888;
}
