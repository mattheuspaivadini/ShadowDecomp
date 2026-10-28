/* GAMECORE.XFF @ 0x0C06D8 (12 B) - setPlayerStatusDisableFadeCompareSwitch
 * Shape `store-arg` recovered by tools/xff_shapes.py and proved by
 * recompiling it byte-exactly (relocations masked).
 * Evidence: `lui` + `sw $a0,lo(...)` + `jr $ra` - writes the argument to .data+0x173c.
 */
extern int D_kernel_data_173C;

void setPlayerStatusDisableFadeCompareSwitch(int a0) {
    D_kernel_data_173C = a0;
}
