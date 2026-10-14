/* STATUS (Session 7, 2026-10-14): NON_MATCHING. best score 15 [cc=29, default].
 * 0156A8 twin (end p+0x100).
 * The original .s stays in the build (asm/cod/015710.s); this C
 * draft (subagent-produced, Session 7) is kept for the record. */
/* asm/cod/015710.s -> func_00115710 @ 0x00115710 (0x64 bytes, 25 insns)
 *
 * Exact twin of func_001156A8 (asm/cod/0156A8.s): same record field, same
 * 0x334-stride table D_0014B598, same 0x80/0x7C offsets, same branchless
 * `cond ? q : p` select - the only difference is the range-clear end:
 *
 *   p = D_0014B598[index].buf;                ; lw $v1,0x10(rec)
 *   q = (int *)((char *)p + 0x80);
 *   func_001318C0((int)p, (int)p + 0x100);    ; end = p + 0x100 (0156A8: 0xFF)
 *   return (p->f7C < q->f7C) ? q : p;
 *
 * Frame 0x20, $ra at 0x10, both pointers spilled (sp+0x00 / sp+0x04). The
 * literal stride 0x334 is the R5900 3-operand `mult` shape.
 * MATCH GUESS: cc=29
 */
struct S015710 {
    char pad00[0x10];
    int *buf;           /* 0x10 */
    char pad14[0x320];  /* to 0x334 */
};

extern struct S015710 D_0014B598[];   /* .bss 0x0014B598: 16 records */

void func_001318C0(int a0, int a1);

int func_00115710(int index) {
    int *p;
    int *q;

    p = D_0014B598[index].buf;
    q = (int *)((char *)p + 0x80);
    func_001318C0((int)p, (int)p + 0x100);
    return (*(int *)((char *)p + 0x7C) < *(int *)((char *)q + 0x7C))
               ? (int)q
               : (int)p;
}
