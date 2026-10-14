/* STATUS (Session 7, 2026-10-14): NON_MATCHING. best score 4 [cc=296, default].
 * GS packet + sceGsSyncPath/PutDrawEnv.
 * The original .s stays in the build (asm/cod/006310.s); this C
 * draft (subagent-produced, Session 7) is kept for the record. */
/* asm/cod/006310.s -> func_00106310 @ 0x00106310 (0x70 bytes, 28 insns)
 *
 * GS draw-env packet setup through the 0x20000000 RAM mirror:
 *   p = (long long *)((unsigned int)D_001321A0 | 0x20000000);
 *   func_00114020(p + 4, 0);          ; fills the 0x40-byte packet at +0x20
 *   p[4] = 0x48; p[3] = 0x47; p[2] = 0x20000;
 *   sceGsSyncPath(0, 0);
 *   sceGsPutDrawEnv(p);
 *   func_001059D8();                  ; tail `j` (frame torn down in the slot)
 * The base is built as `lui $s0,%hi(D_001321A0); addiu; or $s0,$s0,$v0` with
 * $v0 = 0x20000000, i.e. the source ORs the symbol address (the addend +0x20 is
 * the `%lo(D_20000020)` spimdisasm fabricates from that same lui). The three
 * stores are `sd` (qwords), so the pointer is a 64-bit-element type.
 * MATCH GUESS: cc=296 (sibling tail call: `ld`s then `j` with the frame teardown
 * in the delay slot)
 */
int func_00114020(long long *p, short a1);
int sceGsSyncPath(int mode, int timeout);
int sceGsPutDrawEnv(void *env);
int func_001059D8(void);
extern int D_001321A0[];   /* .data 0x001321A0, 0xA0 bytes, address taken (lui/%lo) */

void func_00106310(void) {
    long long *p = (long long *)((unsigned int)D_001321A0 | 0x20000000);

    func_00114020(p + 4, 0);
    p[4] = 0x48;
    p[3] = 0x47;
    p[2] = 0x20000;
    sceGsSyncPath(0, 0);
    sceGsPutDrawEnv(p);
    func_001059D8();
}
