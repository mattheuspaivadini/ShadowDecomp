/* GAMECORE.XFF @ 0x0154D8 (12 B) - setSavedPlaceId
 * Shape `store-arg` recovered by tools/xff_shapes.py and proved by
 * recompiling it byte-exactly (relocations masked).
 * Evidence: `lui` + `sw $a0,lo(...)` + `jr $ra` - writes the argument to .bss+0xc58.
 */
extern char D_kernel_bss_0C58;

void setSavedPlaceId(char a0) {
    D_kernel_bss_0C58 = a0;
}
