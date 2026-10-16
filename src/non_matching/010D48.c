/* STATUS (Session 7, 2026-10-14): NON_MATCHING. best score 20 [cc=29, default].
 * list pop/relink with tag word.
 * The original .s stays in the build (asm/cod/010D48.s); this C
 * draft (subagent-produced, Session 7) is kept for the record. */
/* asm/cod/010D48.s -> func_00110D48 @ 0x00110D48 (0x70 bytes, 28 insns)
 *
 * Pop the head node off the D_00133918 list at 0x14, stamp it with a
 * sequence-derived tag and return the node's identity ORed with that tag:
 *   n = D_00133918.f14;                       ; lw $a2,0x14($a3)
 *   if (n == 0) return 0x80008005;            ; bnez over the error return
 *   v = (unsigned int)n << 4;                 ; sll $a1,$a2,4
 *   n->f28 = 0;                               ; sw $zero,0x28($a2)
 *   D_00133918.f10 = D_00133918.f10 + 1;
 *   n->f0C = 0;
 *   D_00133918.f14 = n->next;                 ; lw $a0,0x0($a2)
 *   D_00133918.f0C = D_00133918.f0C + 1;
 *   n->f18 = 0;                               ; sd $zero,0x18($a2)
 *   n->f08 = ((D_00133918.f0C << 1) & 0x3FE) | 1;
 *   return v | n->f08;                        ; reloads n->f08 (`or $v0,$a1,$v0`)
 * The statement order follows the store order in the asm (0x28, 0x10, 0x0C,
 * 0x14, 0x0C, 0x18, 0x08); the 0x0C counter is read twice (increment, then the
 * tag) and n->f08 is read back after being written, hence the reloads. The
 * node's own 0x04/0x10/0x14/0x20/0x24 fields are untouched by this function.
 * The callers (010DB8, cc=29) pass no arguments. MATCH GUESS: cc=29
 */
struct N10D48 {
    struct N10D48 *next;    /* 0x00 */
    int            f04;     /* 0x04 */
    int            f08;     /* 0x08 */
    int            f0C;     /* 0x0C */
    int            f10;     /* 0x10 */
    int            f14;     /* 0x14 */
    long long      f18;     /* 0x18 */
    int            f20;     /* 0x20 */
    int            f24;     /* 0x24 */
    int            f28;     /* 0x28 */
};

struct D10D48 {
    int             pad00;  /* 0x00 */
    int             pad04;  /* 0x04 */
    int             pad08;  /* 0x08 */
    int             f0C;    /* 0x0C */
    int             f10;    /* 0x10 */
    struct N10D48  *f14;    /* 0x14 */
};

extern struct D10D48 D_00133918;

int iAllocTimerCounter(void) {
    struct N10D48 *n;
    unsigned int v;

    n = D_00133918.f14;
    if (n == 0)
        return 0x80008005;
    v = (unsigned int)n << 4;
    n->f28 = 0;
    D_00133918.f10 = D_00133918.f10 + 1;
    n->f0C = 0;
    D_00133918.f14 = n->next;
    D_00133918.f0C = D_00133918.f0C + 1;
    n->f18 = 0;
    n->f08 = ((D_00133918.f0C << 1) & 0x3FE) | 1;
    return (int)(v | n->f08);
}
