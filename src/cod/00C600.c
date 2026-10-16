/* asm/cod/00C600.s -> func_0010C600 @ 0x0010C600 (0x1C bytes)
 *   jal sceStdioCCode with a1 = 0x10
 */
extern int sceStdioCCode();

int sceDelDrv(int a0) {
    return sceStdioCCode(a0, 0x10);
}
