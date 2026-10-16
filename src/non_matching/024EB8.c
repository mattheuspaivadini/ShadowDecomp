/* STATUS (Session 7, 2026-10-14): NON_MATCHING. best score 15 [cc=296, default].
 * handler-list run + framed tail.
 * The original .s stays in the build (asm/cod/024EB8.s); this C
 * draft (subagent-produced, Session 7) is kept for the record. */
/* asm/cod/024EB8.s -> func_00124EB8 @ 0x00124EB8 (0x8C bytes, 35 insns)
 * Run the D_00135964 handler list, then arm the one-shot flag:
 *   p = D_00135964 (the global is a cursor into a zero-terminated array of
 *   function pointers); while (*p) { D_00135964 = p + 1; (*p)(); p =
 *   D_00135964; }  -- the global is re-read after every callback (`jalr`), and
 *   the loop test reloads it too (`bnel` with `lw $a0,0x0($s0)` in the delay
 *   slot);
 *   if (D_00135968 == 0) { D_00135968 = 1; func_001261D8((int)D_001360E0); }
 *   -- a framed sibling tail call (`j func_001261D8` with `addiu $sp` in its
 *   delay slot) through the early-return `bnez` shape.
 * MATCH GUESS: cc=296 (0x125xxx/0x126xxx neighbourhood: 025008/026298) */
typedef void (*VFP)(void);

extern VFP *D_00135964[];   /* cursor into the handler table (lui/%lo) */
extern int D_00135968[];    /* one-shot "already armed" flag (lui/%lo) */
extern char __EH_FRAME_BEGIN__[];   /* the argument handed to func_001261D8 */

int __deregister_frame_info(int key);

void __do_global_dtors(void) {
    VFP *p;

    p = D_00135964[0];
    while (*p != 0) {
        D_00135964[0] = p + 1;
        (*p)();
        p = D_00135964[0];
    }
    if (D_00135968[0] == 0) {
        D_00135968[0] = 1;
        __deregister_frame_info((int)__EH_FRAME_BEGIN__);
    }
}
