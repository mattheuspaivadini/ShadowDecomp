/* GAMECORE.XFF @ 0x05C4C0 (12 B) - SCRFuncHorseStandByFlag
 * Shape `store-arg` recovered by tools/xff_shapes.py and proved by
 * recompiling it byte-exactly (relocations masked).
 * Evidence: `lui` + `sw $a1,lo(...)` + `jr $ra` - writes the argument to .data+0x1318.
 */
extern int D_kernel_data_1318;

void SCRFuncHorseStandByFlag(int a0, int a1) {
    D_kernel_data_1318 = a1;
}
