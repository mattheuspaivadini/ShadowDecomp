/* STATUS (Session 7, 2026-10-14): NON_MATCHING. best score 7 [cc=29, default].
 * init-once around a syscall stub; scheduling differs.
 * The original .s stays in the build (asm/cod/00A740.s); this C
 * draft (subagent-produced, Session 7) is kept for the record. */
/* asm/cod/00A740.s -> func_0010A740 @ 0x0010A740 (0x54 bytes, 21 insns)
 *
 * Init-once wrapper around the raw syscall stub func_00106FE0 (syscall 0x40,
 * v1 = 0x40): the 0x20-byte parameter block on the stack is filled only while
 * D_0013231C is still -1, and the (new or old) handle is returned.
 *
 *   if (D_0013231C == -1) {          (gcc emits `bne v0,-1,end`)
 *       buf[1] = 1;
 *       buf[5] = (int)D_00137F68;    (address passed to the syscall)
 *       buf[2] = 1;
 *       D_0013231C = func_00106FE0(buf);
 *   }
 *   return D_0013231C;               (reuses the stored call result in $v0)
 *
 * The store order (0x04, 0x14, then 0x08 in the jal delay slot) is the asm's,
 * and the frame is 0x40 with buf[8] at 0x00, $s0 at 0x20 and $ra at 0x30.
 * MATCH GUESS: cc=296 (single trailing return + shared epilogue)
 */
extern int D_0013231C __attribute__((section(".data")));
extern char D_00137F68[];

int func_00106FE0(void *args);

int func_0010A740(void) {
    int buf[8];

    if (D_0013231C == -1) {
        buf[1] = 1;
        buf[5] = (int)D_00137F68;
        buf[2] = 1;
        D_0013231C = func_00106FE0(buf);
    }
    return D_0013231C;
}
