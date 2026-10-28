/* GAMECORE.XFF @ 0x018660 (12 B) - gameflowSetJumpSekiban
 * Shape `store-arg` recovered by tools/xff_shapes.py and proved by
 * recompiling it byte-exactly (relocations masked).
 * Evidence: `lui` + `sw $a0,lo(...)` + `jr $ra` - writes the argument to .data+0x7d0.
 */
extern int D_kernel_data_07D0;

void gameflowSetJumpSekiban(int a0) {
    D_kernel_data_07D0 = a0;
}
