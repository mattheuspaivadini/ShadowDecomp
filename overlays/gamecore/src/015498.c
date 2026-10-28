/* GAMECORE.XFF @ 0x015498 (12 B) - setSavedGameTime
 * Shape `store-arg` recovered by tools/xff_shapes.py and proved by
 * recompiling it byte-exactly (relocations masked).
 * Evidence: `lui` + `sw $a0,lo(...)` + `jr $ra` - writes the argument to .bss+0xc6c.
 */
extern int D_kernel_bss_0C6C;

void setSavedGameTime(int a0) {
    D_kernel_bss_0C6C = a0;
}
