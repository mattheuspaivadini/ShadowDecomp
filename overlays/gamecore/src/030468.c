/* GAMECORE.XFF @ 0x030468 (12 B) - bgmEnvTickProckMask
 * Shape `store-arg` recovered by tools/xff_shapes.py and proved by
 * recompiling it byte-exactly (relocations masked).
 * Evidence: `lui` + `sw $a0,lo(...)` + `jr $ra` - writes the argument to .data+0x10c4.
 */
extern int D_kernel_data_10C4;

void bgmEnvTickProckMask(int a0) {
    D_kernel_data_10C4 = a0;
}
