/* asm/cod/009288.s -> func_00109288.
 * SCE sifrpc ring cursor; record address computed before the cursor store (Session 19)
 * MATCHED. */
/* asm/cod/009288.s -> func_00109288 @ 0x00109288 (0x30 bytes, 11 insns)
 *
 * Cursor step through a table of 64-byte records hanging off the same object:
 *
 *   lw    $a1, 0x24($a0)   ; p->f24  (cursor, dividend - loaded first)
 *   lw    $v1, 0x18($a0)   ; p->f18  (record count, divisor)
 *   div/mfhi               ; signed 32-bit modulo
 *   lw    $a1, 0x14($a0)   ; p->f14  (table base) - scheduled into the divide
 *   addiu $v1, $v0, 0x1    ; cursor + 1
 *   sll   $v0, $v0, 6      ; rem * 64
 *   sw    $v1, 0x24($a0)   ; p->f24 = cursor + 1
 *   jr    $ra
 *    addu $v0, $a1, $v0    ; return p->f14 + rem * 64
 *
 * The dividend ($a1 = p->f24) is dead after the divider block, so the allocator
 * reloads $a1 with p->f14 - i.e. the third load belongs to the *return*
 * expression, not to the modulo. `div` (not `divu`) fixes the signed types.
 * MATCH GUESS: cc=29 (the 009xxx family: 009198/009268/0093C8/009690 are cc=29)
 */
struct S009288 {
    char pad00[0x14];
    int  f14;    /* 0x14 table base */
    int  f18;    /* 0x18 record count (modulo) */
    int  f1C;
    int  f20;
    int  f24;    /* 0x24 cursor */
};

int func_00109288(struct S009288 *p) {
    int rem = p->f24 % p->f18;
    int r = p->f14 + rem * 64;

    p->f24 = rem + 1;
    return r;
}
