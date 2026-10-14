/* STATUS (Session 7, 2026-10-14): NON_MATCHING. best score 4 [cc=29, default].
 * 015A30 clone (cmd 0x80001305); bgezl tail.
 * The original .s stays in the build (asm/cod/015D70.s); this C
 * draft (subagent-produced, Session 7) is kept for the record. */
/* asm/cod/015D70.s -> func_00115D70 @ 0x00115D70 (0x60 bytes, 24 insns)
 *
 * Clone of the matched func_00115A30 (src/cod/015A30.c) - the same 9-argument
 * func_00109980() call over the D_0014E900 / D_0014EA00 pair with two 0x90-byte
 * buffers (the 9th argument is the `sw $zero,0x0($sp)` stack word: the EE-EABI
 * outgoing argument area starts at $sp+0) - but with command 0x80001305, and
 * with a conditional tail:
 *
 *   r = func_00109980(&D_0014E900, 0x80001305, 0, &D_0014EA00, 0x90,
 *                     &D_0014EA00, 0x90, 0, 0);
 *   return (r >= 0) ? D_0014EA00[1] : 0;
 *
 * `bgezl $v0` with the `lw $v0,0x4($s0)` in its delay slot is the ternary
 * lowering; D_0014EA00 is held in $s0 for the tail load, exactly as the matched
 * 015A30.c holds it. cc=29: 015A30.c and the neighbouring 015D28.c are cc=29
 * TUs (16-byte-spaced $s0/$ra frame).
 * MATCH GUESS: cc=29 */
extern int D_0014E900[];   /* .bss 0x0014E900, 0x50 bytes (lui/%lo) */
extern int D_0014EA00[];   /* .bss 0x0014EA00, 0xC0 bytes (lui/%lo) */

int func_00109980(int a0, int a1, int a2, int a3, int a4, int a5, int a6,
                  int a7, int a8);

int func_00115D70(void) {
    int r = func_00109980((int)D_0014E900, (int)0x80001305, 0, (int)D_0014EA00,
                          0x90, (int)D_0014EA00, 0x90, 0, 0);

    return r >= 0 ? D_0014EA00[1] : 0;
}
