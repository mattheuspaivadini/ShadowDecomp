/* STATUS (Session 7, 2026-10-14): NON_MATCHING. best score 2 [cc=29, default].
 * 00AAC8 clone on other tables.
 * The original .s stays in the build (asm/cod/00E338.s); this C
 * draft (subagent-produced, Session 7) is kept for the record. */
/* asm/cod/00E338.s -> func_0010E338 @ 0x0010E338 (0x8C bytes, 35 insns)
 *
 * Clone of the matched func_0010AAC8 (00AAC8.c): the same three-way memcmp
 * (func_00128188) over the id words D_001475A8 / D_0013227C and the runtime
 * word D_00132334:
 *
 *   r = 0;
 *   if (memcmp(D_001475A8, D_0013227C, 4)        != 0)   ; $a0/$a1/$a2 = 4
 *       if (memcmp(D_001475A8, D_00132334, 4)    != 0)
 *           r = memcmp(D_0013227C, D_00132334, 4) != 0;  ; sltu $s2,$zero,$v0
 *   return r;
 *
 * D_00132334 is re-loaded around the calls and its `lui` half is kept in $s0,
 * so it is a non-small 4-byte scalar (lui/%lo); D_001475A8 is the 4-byte
 * object the sibling func_0010E238 copies D_00147380 into (lwl/lwr - swl/swr).
 * MATCH GUESS: cc=29 (the sibling 00E238/00E3C8 family; 16-byte-stride
 * $s0..$s3 saves) */
extern char D_0013227C[];   /* .data/.bss 4-byte id word (lui/addiu) */
extern char D_001475A8[];   /* .data/.bss 4-byte id word (lui/addiu) */
extern int  D_00132334[];   /* 4-byte scalar; `lw %lo(..)($s0)` -> non-small */

int func_00128188(void *a0, void *a1, int a2);

int func_0010E338(void) {
    int r = 0;

    if (func_00128188(D_001475A8, D_0013227C, 4) != 0) {
        if (func_00128188(D_001475A8, (void *)D_00132334[0], 4) != 0) {
            r = func_00128188(D_0013227C, (void *)D_00132334[0], 4) != 0;
        }
    }
    return r;
}
