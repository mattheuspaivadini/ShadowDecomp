/* STATUS (Session 7, 2026-10-14): NON_MATCHING. best score 11 [cc=29, default].
 * stack block build + func_001211B8 store.
 * The original .s stays in the build (asm/cod/01CAC0.s); this C
 * draft (subagent-produced, Session 7) is kept for the record. */
/* asm/cod/01CAC0.s -> func_0011CAC0 @ 0x0011CAC0 (0x58 bytes, 22 insns)
 *
 * Collect four words of a 0x24-byte record into a stack block and hand it to
 * func_001211B8(index, block) (the 16-byte block-store helper, matched
 * 0211B8.c, whose second argument is that same 4-word block):
 *
 *   w28  = *(unsigned short *)(rec + 0x28);       lhu $a2,0x28($v1)
 *   w2C  = *(unsigned short *)(rec + 0x2C);       lhu $a3,0x2C($v1)
 *   buf[0] = w28;                                 sw $a4,0x0($sp)
 *   buf[1] = w2C;                                 sw $a3,0x4($sp)
 *   buf[3] = 1;                                   sw $a5,0xC($sp)
 *   buf[2] = (rec->field30 << 10) / w28;          sll/mflo, div $zero,$v0,$a2
 *   return func_001211B8(index, buf);             sw $v0,0x8($sp) in the shadow
 *
 * The divisor is a *zero-extended halfword* promoted to int, so the division is
 * the signed `div` (with the `beql ...,break 0,7` zero-check in its shadow), not
 * `divu`. Store order in the buffer is 0x0, 0x4, 0xC, 0x8 - the quotient lands
 * in the jal delay slot.
 * MATCH GUESS: cc=296 (delay slots filled; the 0x24-record indexing is
 * func_001211B8's own, this caller only builds the block)
 */
int _sceMcCoreSetCardSpec(int index, int *src);

int func_0011CAC0(int index, int *rec) {
    unsigned short w28;
    int buf[4];

    w28 = *(unsigned short *)((char *)rec + 0x28);
    buf[0] = w28;
    buf[1] = *(unsigned short *)((char *)rec + 0x2C);
    buf[3] = 1;
    buf[2] = (*(int *)((char *)rec + 0x30) << 10) / w28;
    return _sceMcCoreSetCardSpec(index, buf);
}
