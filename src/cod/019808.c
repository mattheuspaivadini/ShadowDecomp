/* MATCHED (Session 5, step 2; named in step 4). Evidence: tools/permute.py ->
 * build/permute/019808. Name evidence: func_00104668 calls this routine at
 * 0x001047C4 and prints "wait_get_addr_only() failed.\n" (D_00137140) when it
 * returns negative -> the routine implements wait_get_addr_only (UNCONFIRMED:
 * the inference is the message-next-to-call rule, see config/symbol_addrs.txt).
 *
 * asm/cod/019808.s -> wait_get_addr_only @ 0x00119808 (0x34 bytes)
 *   addiu $sp, $sp, -0x10
 *   andi  $a5, $a5, 0x2
 *   beqz  $a5, .L00119828
 *    sd   $ra, 0x0($sp)
 *   jal   func_00119670
 *    nop
 *   b     .L00119834
 *    ld   $ra, 0x0($sp)
 * .L00119828:
 *   jal   func_00119708
 *    nop
 *   ld    $ra, 0x0($sp)
 * .L00119834:
 *   jr    $ra
 *    addiu $sp, $sp, 0x10
 */
int func_00119670(int a0, int a1, int a2, int a3, int a4);
int func_00119708(int a0, int a1, int a2, int a3, int a4);

int wait_get_addr_only(int a0, int a1, int a2, int a3, int a4, int a5) {
    if (a5 & 2)
        return func_00119670(a0, a1, a2, a3, a4);
    return func_00119708(a0, a1, a2, a3, a4);
}
