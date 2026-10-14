/* asm/cod/00D408.s -> func_0010D408 @ 0x0010D408 (0x1C bytes)
 *   jal sceStdioCCode with a1 = 0x15
 */
extern int sceStdioCCode();

int func_0010D408(int a0) {
    return sceStdioCCode(a0, 0x15);
}
