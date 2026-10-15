/* asm/cod/00F550.s -> func_0010F550.
 * byte-exact under EE-GCC 2.95.3-136 (PE/wine)
 * MATCHED (Session 8). */
/* asm/cod/00F550.s -> func_0010F550 @ 0x0010F550 (0x40 bytes, 14 insns)
 *
 * Two-way branch on a syscall result:
 *
 *   jal  func_00107440                 ; `addiu $v1,$zero,0x7F; syscall 0`
 *   lui  $v1, (0x2000000 >> 16)         ; v1 = 0x02000000 (pure `lui`)
 *   bne  $v0, $v1, .L0010F57C
 *   jal  func_0010F590                 ; won't-take path: big handler
 *   b    .L0010F588
 *    ld  $ra, 0x0($sp)                 ; frame popped, `ld` in the b slot
 * .L0010F57C:
 *   jal  func_00107450                 ; `addiu $v1,$zero,0x82; syscall 0`
 *   ld   $ra, 0x0($sp)
 * .L0010F588:
 *   jr   $ra
 *    addiu $sp, $sp, 0x10
 *
 * Both calls are plain statements and no $v0 is set on either path, so the
 * function is void; `bne` (not `beq`) makes the *fall-through* the
 * `r == 0x02000000` path. The `ld $ra` duplicated into both paths is the
 * delay-slot-filled variant: try -g0 as well if -g2 leaves the `ld` only at
 * the join.
 *
 * NOTE: both calls sit in tail position, yet the image keeps `jal` + a real
 * epilogue - this TU must have sibling-call optimisation disabled
 * (`-fno-optimize-sibling-calls`, the per-TU flag of the wrapper tier), which
 * the 2.9 cc1 rejects, so the revision is cc=296. The caller 010118.c already
 * declares this function `void func_0010F550(void)`.
 * MATCH GUESS: cc=296 + -fno-optimize-sibling-calls
 */
int func_00107440(void);
void func_0010F590(void);
void func_00107450(void);

void func_0010F550(void) {
    if (func_00107440() == 0x2000000) {
        func_0010F590();
    } else {
        func_00107450();
    }
}
