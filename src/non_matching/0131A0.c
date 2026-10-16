/* STATUS (Session 7, 2026-10-14): NON_MATCHING. best score 8 [cc=29, default].
 * arena packet opener (0130F0 family).
 * The original .s stays in the build (asm/cod/0131A0.s); this C
 * draft (subagent-produced, Session 7) is kept for the record. */
/* asm/cod/0131A0.s -> func_001131A0 @ 0x001131A0 (0x58 bytes, 22 insns)
 *
 * DMAC/GIF packet opener, same arena object as func_001130F0/func_00113148
 * (0x00 = write cursor, 0x0C = block to credit):
 *
 *   func_001132E8(p, 2, 3)                 ; arena step (2, 3 = packet kind)
 *   q = p->field00                         ; lw  $a1,0x0($s0)
 *   v = flag ? 0xD0000000 : 0x50000000     ; lui $v0 / lui $a0 / movn $a0,$v0,$s1
 *   p->field00 = (char *)q + 4             ; addiu $v1,$a1,0x4 ; sw $v1,0x0($s0)
 *   p->field0C = q                         ; sw $a1,0xC($s0)
 *   q[0] = v                               ; sw $a0,0x0($a1)
 *
 * The two `lui` constants are the whole source of the values: `movn $a0,$v0,$s1`
 * yields 0xD0000000 when the second argument is non-zero, 0x50000000 otherwise
 * (the "else" value sits in the destination register). $s1 holds the flag
 * across the call and $s0 the record pointer, hence the 0x30 frame with
 * $s0/$s1/$ra. The store order follows the asm (0x00, 0x0C, q[0]).
 * MATCH GUESS: cc=29
 */
struct S0131A0 {
    int *field00;                   /* 0x00 write cursor */
    int  field04;                   /* 0x04 */
    int  field08;                   /* 0x08 */
    int *field0C;                   /* 0x0C block to credit */
};

void sceVif1PkAlign(struct S0131A0 *p, int a1, int a2);

void sceVif1PkOpenDirectCode(struct S0131A0 *p, int flag) {
    int *q;
    int v;

    sceVif1PkAlign(p, 2, 3);
    q = p->field00;
    v = flag ? (int)0xD0000000 : (int)0x50000000;
    p->field00 = (int *)((char *)q + 4);
    p->field0C = q;
    q[0] = v;
}
