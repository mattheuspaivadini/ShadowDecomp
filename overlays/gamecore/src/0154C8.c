/* GAMECORE.XFF @ 0x0154C8 (12 B) - getSavedPlaceId
 * Shape `ret-load` recovered by tools/xff_shapes.py and proved by
 * recompiling it byte-exactly (relocations masked).
 * Evidence: `lui` + `jr $ra` + delay `lb $v0,lo(...)` against .bss+0xc58 - returns that object as `char`.
 */
extern char D_kernel_bss_0C58;

char getSavedPlaceId(void) {
    return D_kernel_bss_0C58;
}
