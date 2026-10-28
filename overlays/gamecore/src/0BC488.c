/* GAMECORE.XFF @ 0x0BC488 (12 B) - setEventScriptEnable
 * Shape `store-arg` recovered by tools/xff_shapes.py and proved by
 * recompiling it byte-exactly (relocations masked).
 * Evidence: `lui` + `sw $a0,lo(...)` + `jr $ra` - writes the argument to .data+0x1728.
 */
extern int D_kernel_data_1728;

void setEventScriptEnable(int a0) {
    D_kernel_data_1728 = a0;
}
