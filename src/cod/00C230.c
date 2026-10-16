/* asm/cod/00C230.s -> func_0010C230 @ 0x0010C230 (0x1C bytes)
 *   jal sceStdioCCode with a1 = 8
 */
extern int sceStdioCCode();

int sceRmdir(int a0) {
    return sceStdioCCode(a0, 8);
}
