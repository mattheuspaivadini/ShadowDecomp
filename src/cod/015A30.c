/* asm/cod/015A30.s -> func_00115A30 @ 0x00115A30 (0x54 bytes, 21 insns)
 *
 * Register a modId/buffer pair and return the first word of the second buffer:
 *
 *   func_00109980(&D_0014E900, 0x80001363, 0, &D_0014EA00, 0x90,
 *                 &D_0014EA00, 0x90, 0, 0);
 *   return D_0014EA00[0];            ; lw $v0,%lo(D_0014EA00)($s0)
 *
 * $a0-$a7 carry the first eight arguments (EE EABI: $a0-$a3 + $a4-$a7), and the
 * ninth is the `sw $zero,0x0($sp)` stack word - in this ABI the outgoing
 * argument area starts at $sp+0 (func_00109980 itself reads its 9th argument at
 * 0xC0($sp), right past its 0xC0 frame). The same call shape appears in the
 * sibling asm/cod/00DE60.s.
 * MATCH GUESS: cc=296 (delay slots filled: $a7 and the frame setup sit in the
 * jal shadow)
 */
extern int D_0014E900[];   /* .bss 0x0014E900, 0x50 bytes (lui/%lo) */
extern int D_0014EA00[];   /* .bss 0x0014EA00, 0xC0 bytes (lui/%lo) */

int func_00109980(int a0, int a1, int a2, int a3, int a4, int a5, int a6,
                  int a7, int a8);

int func_00115A30(void) {
    func_00109980((int)D_0014E900, (int)0x80001363, 0, (int)D_0014EA00, 0x90,
                  (int)D_0014EA00, 0x90, 0, 0);
    return D_0014EA00[0];
}
