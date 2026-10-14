/* asm/cod/0221D0.s -> func_001221D0 @ 0x001221D0 (0x40 bytes, 14 insns)
 *
 * "id = func_00122128(); clear the D_00167F00 tracking block; return id":
 *
 *   addiu $sp, $sp, -0x20
 *   sd    $s0, 0x0($sp)
 *   sd    $ra, 0x10($sp)
 *   jal   func_00122128               ; id = ...
 *   lui   $a0, %hi(D_00167F00)
 *   daddu $s0, $v0, $zero             ; keep the id across the second call
 *   addiu $a0, $a0, %lo(D_00167F00)   ; arg0 = &D_00167F00
 *   daddu $a1, $zero, $zero           ; arg1 = 0 (fill value)
 *   jal   func_001283D0               ; memset-like: (dst, value, size)
 *   addiu $a2, $zero, 0x310           ; arg2 = 0x310
 *   daddu $v0, $s0, $zero             ; return the saved id
 *   ld    $ra, 0x10($sp)
 *   ld    $s0, 0x0($sp)
 *   jr    $ra
 *    addiu $sp, $sp, 0x20
 *
 * func_001283D0 is the memset-like filler (its own asm tests `size < 8` and
 * `dst & 0xF` before picking the word path); D_00167F00 is the 0x1000-byte .bss
 * block also used by the matched 022DA0.c/022D68.c, but here its address is
 * passed on, so it is declared as an array (absolute lui/%lo addressing).
 * The saved id is returned through $s0, so the return is a separate statement
 * (`int id = f(); g(...); return id;`), never a tail call.
 * MATCH GUESS: cc=29 (the 0221xx/0222xx family is cc=29 throughout)
 */
int  func_00122128(void);
int  func_001283D0(void *dst, int value, int size);

extern int D_00167F00[];    /* .bss 0x00167F00, 0x1000 bytes */

int func_001221D0(void) {
    int id = func_00122128();

    func_001283D0(D_00167F00, 0, 0x310);
    return id;
}
