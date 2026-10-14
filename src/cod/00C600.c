/* asm/cod/00C600.s -> func_0010C600 @ 0x0010C600 (0x1C bytes)
 *   jal func_0010BEA8 with a1 = 0x10
 */
extern int func_0010BEA8();

int func_0010C600(int a0) {
    return func_0010BEA8(a0, 0x10);
}
