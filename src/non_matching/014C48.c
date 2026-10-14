/* STATUS (Session 7, 2026-10-14): NON_MATCHING. best score 8 [cc=29, default].
 * normalise + conditional field store.
 * The original .s stays in the build (asm/cod/014C48.s); this C
 * draft (subagent-produced, Session 7) is kept for the record. */
/* asm/cod/014C48.s -> func_00114C48 @ 0x00114C48 (0x68 bytes, 26 insns)
 *
 * Reset/program a DMA-channel control block `p` with a normalised mode value
 * (the 0148xx-0150xx libdma block; 0148B8/0147C0 are matched siblings):
 *
 *   r = func_001148B8(x);                  ; normalise the mode word
 *   func_001147C0(p);                      ; wait for the channel (0x70-byte spin)
 *   if (p->f30 != 0xFFFFFFFF)              ; bnel: the store is in the taken
 *       p->f30 = r;                        ; delay slot => only when != -1
 *   v = p->f00;                            ; lw BEFORE the 0x20 clear below
 *   p->f20 = 0;
 *   p->f00 = (v & ~0xC) | 0x105;           ; and -13 / ori 0x105
 *   return p->f00;                         ; $v0 already holds the new word
 *
 * Frame 0x30: $s0 (p) at 0x00, $s1 (r) at 0x10, $ra at 0x20 - the cc=29 slot
 * layout of this family.
 * MATCH GUESS: cc=29
 */
unsigned int func_001148B8(unsigned int x);
int func_001147C0(unsigned *p);

int func_00114C48(int *p, unsigned int x) {
    int r;
    int v;

    r = func_001148B8(x);
    func_001147C0((unsigned *)p);
    if (p[0xC] != -1)
        p[0xC] = r;
    v = p[0];
    p[8] = 0;
    v = (v & -13) | 0x105;
    p[0] = v;
    return v;
}
