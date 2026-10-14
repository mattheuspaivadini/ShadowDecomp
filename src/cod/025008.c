/* asm/cod/025008.s -> func_00125008 @ 0x00125008 (0x38 bytes, 12 insns)
 *
 * One-shot initialisation guard around D_00169F88 (a 4-byte .bss flag):
 *
 *   lui   $v0, %hi(D_00169F88)
 *   addiu $a0, $v0, %lo(D_00169F88)   ; p = &D_00169F88 (address reused for
 *   lw    $v1, 0x0($a0)               ;  the load and the store, hence $a0)
 *   bnez  $v1, .L00125038
 *    ld   $ra, 0x0($sp)               ; already-flag-set path: return
 *   addiu $v0, $zero, 0x1
 *   sw    $v0, 0x0($a0)               ; flag = 1
 *   j     func_00124F48               ; tail call, frame popped in the slot
 *    addiu $sp, $sp, 0x10
 * .L00125038:
 *   jr    $ra
 *    addiu $sp, $sp, 0x10
 *
 * The frame exists only for the tail call and the early path leaves $v0 as the
 * `lui` value (no `daddu v0,zero`), so the function is void and the early exit
 * is a bare `return;`; `start` (asm/cod/003B40.s) calls it and ignores $v0.
 * The framed `j` is the cc=296 sibling-call shape (matched 003008.c).
 * MATCH GUESS: cc=296
 */
extern int D_00169F88[];    /* .bss 0x00169F88, 4 bytes: array => lui/%lo */

void func_00124F48(void);

void func_00125008(void) {
    if (D_00169F88[0] != 0)
        return;
    D_00169F88[0] = 1;
    func_00124F48();
}
