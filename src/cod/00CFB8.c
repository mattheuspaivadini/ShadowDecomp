/* asm/cod/00CFB8.s -> func_0010CFB8 @ 0x0010CFB8 (0x1C bytes)
 *   jal sceStdioCCode with a1 = 0x12
 */
extern int sceStdioCCode();

int sceChdir(int a0) {
    return sceStdioCCode(a0, 0x12);
}
