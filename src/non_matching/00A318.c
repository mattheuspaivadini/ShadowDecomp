/* STATUS (Session 7, 2026-10-14): NON_MATCHING. best score 16 [cc=29, default].
 * 16-byte record accessors around D_00146EC0.
 * The original .s stays in the build (asm/cod/00A318.s); this C
 * draft (subagent-produced, Session 7) is kept for the record. */
/* asm/cod/00A318.s -> func_0010A318 @ 0x0010A318 (0x6C bytes, 27 insns)
 *
 * Slot accessor on top of func_0010A0B0's one-shot init:
 *   func_0010A0B0();
 *   func_00107020(D_00132320[0]);          ; lw $a0,%lo(D_00132320)($s1)
 *   if (a0 < 0x20) {                       ; unsigned -> sltiu
 *       func_00107000(D_00132320[0]);
 *       return (int)&D_00146EC0[a0];       ; 16-byte records
 *   }
 *   func_00107000(D_00132320[0]);
 *   return 0;
 * The call is duplicated in both arms (the tail of each arm is `jal
 * func_00107000` with the D_00132320 reload in its delay slot), and the good
 * arm returns the record address built as `sll $s0,$s0,4` + `addu $s0,$s0,$v0`
 * (a0 is kept in $s0 across the call and copied into $v0 at the end).
 * MATCH GUESS: cc=29 (00A798 / the func_00107020 block)
 */
struct S16 { char b[16]; };

extern int D_00132320[];            /* .data 0x00132320, 4 bytes (lui/%lo) */
extern struct S16 D_00146EC0[];     /* .bss  0x00146EC0, 0x200 bytes */
int func_0010A0B0(void);
int func_00107020(int a0);
int func_00107000(int a0);

int func_0010A318(unsigned int a0) {
    func_0010A0B0();
    func_00107020(D_00132320[0]);
    if (a0 < 0x20) {
        func_00107000(D_00132320[0]);
        return (int)&D_00146EC0[a0];
    }
    func_00107000(D_00132320[0]);
    return 0;
}
