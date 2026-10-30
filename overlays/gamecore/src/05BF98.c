/* GAMECORE.XFF @ 0x05BF98 (12 B) - setHorseAIStopFlag
 * Shape `store-arg` recovered by tools/xff_shapes.py and proved by
 * recompiling it byte-exactly (relocations masked).
 * Evidence: `lui` + `sw $a0,lo(...)` + `jr $ra` - writes the argument to .data+0x1314.
 */
extern int D_kernel_data_1314;

void setHorseAIStopFlag(int a0) {
    D_kernel_data_1314 = a0;
}
