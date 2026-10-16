/* asm/cod/0199A0.s -> func_001199A0 @ 0x001199A0 (0x24 bytes, 9 insns)
 *   addiu $v0, $zero, 0x1                 ; v0 = 1
 *   bne   $a0, $v0, .L001199BC            ; if (a0 != 1) return
 *    lui  $v0, %hi(D_00135618)            ; (delay slot: runs either way)
 *   addiu $a0, $zero, 0x1
 *   sw    $zero, %lo(D_00135618)($v0)     ; D_00135618 = 0
 *   j     func_001128E8                   ; func_001128E8(1, 0)
 *    daddu $a1, $zero, $zero
 * .L001199BC:
 *   jr    $ra
 *    nop
 *
 * Registered as a callback in func_001198B8 (command 0x80000014, after the
 * once-only flag D_00135618 was set to 1 and the func_001128D0(1) poll loop
 * finished): a0 == 1 clears the once-only flag and runs the D_0014B500 setter
 * with slot 1 = 0, i.e. the reset/release path.
 *
 * Split `lui` + separate `%lo` store operand and the bare tail `j` (no frame)
 * are the 2.9 generation shapes (docs/compiler.md 4.3, same as the matched
 * 0128D0/0128E8/009198).
 * MATCH GUESS: cc=29 */
extern __attribute__((section(".data"))) int D_00135618;   /* .data 0x00135618 */

int sceSifSetSreg(int index, int value);

void func_001199A0(int a0) {
    if (a0 == 1) {
        D_00135618 = 0;
        sceSifSetSreg(1, 0);
    }
}
