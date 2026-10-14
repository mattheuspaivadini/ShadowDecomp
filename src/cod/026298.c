/* asm/cod/026298.s -> func_00126298 @ 0x00126298 (0x20 bytes, 8 insns)
 *   addiu $sp, $sp, -0x10
 *   sd    $ra, 0x0($sp)
 *   jal   func_001261D8             ; list lookup by key; $a0 is left alone
 *    nop
 *   ld    $ra, 0x0($sp)
 *   daddu $a0, $v0, $zero           ; a0 = the node that was found
 *   j     func_001277C0
 *    addiu $sp, $sp, 0x10
 *
 * Look the node up by key (func_001261D8 walks D_00169F90 comparing the node's
 * field 0x08 against $a0) and hand that node - with no second argument - to
 * func_001277C0, which releases it for the D_00135C60 pool.
 *
 * Framed `jal` plus framed tail call: the cc=296 shape.
 * MATCH GUESS: cc=296 */
int func_001261D8(int key);
int func_001277C0(int node);

int func_00126298(int key) {
    return func_001277C0(func_001261D8(key));
}
