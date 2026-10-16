/* STATUS (Session 7, 2026-10-14): NON_MATCHING. best score 15 [cc=29, default].
 * range clear + branchless pointer select.
 * The original .s stays in the build (asm/cod/0156A8.s); this C
 * draft (subagent-produced, Session 7) is kept for the record. */
/* asm/cod/0156A8.s -> func_001156A8 @ 0x001156A8 (0x64 bytes, 25 insns)
 *
 * Clear the 0x100-byte buffer of record `index` in the 0x334-stride table
 * D_0014B598 and return the side whose word at 0x7C is larger:
 *
 *   p = D_0014B598[index].buf;                ; lw $v1,0x10(rec)
 *   q = (int *)((char *)p + 0x80);
 *   func_001318C0((int)p, (int)p + 0xFF);     ; range clear p..p+0xFF
 *   return (p->f7C < q->f7C) ? q : p;         ; branchless select of the two
 *                                             ; spilled pointers: slt, sll 2,
 *                                             ; addu $sp, lw
 *
 * p and q are spilled to the 0x20 frame (sp+0x00 / sp+0x04) because they
 * survive the call; the frame saves only $ra (no callee-saved register is
 * touched). The literal stride 0x334 is the R5900 3-operand `mult` shape.
 * MATCH GUESS: cc=29
 */
struct S0156A8 {
    char pad00[0x10];
    int *buf;           /* 0x10 */
    char pad14[0x320];  /* to 0x334 */
};

extern struct S0156A8 D_0014B598[];   /* .bss 0x0014B598: 16 records */

void SyncDCache(int a0, int a1);

int func_001156A8(int index) {
    int *p;
    int *q;

    p = D_0014B598[index].buf;
    q = (int *)((char *)p + 0x80);
    SyncDCache((int)p, (int)p + 0xFF);
    return (*(int *)((char *)p + 0x7C) < *(int *)((char *)q + 0x7C))
               ? (int)q
               : (int)p;
}
