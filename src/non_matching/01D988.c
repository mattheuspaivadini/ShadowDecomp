/* STATUS (Session 7, 2026-10-14): NON_MATCHING. best score 8 [cc=29, default].
 * func_0011BFB0/BBB8/BB48 chain; movn lowering.
 * The original .s stays in the build (asm/cod/01D988.s); this C
 * draft (subagent-produced, Session 7) is kept for the record. */
/* asm/cod/01D988.s -> func_0011D988 @ 0x0011D988 (0x60 bytes, 24 insns)
 *
 * Two-stage check over the record in $a2 (a1/a2 are only forwarded, $a2 is the
 * one kept in $s0 across the calls):
 *
 *   if (func_0011BFB0(a0, a1, a2) != 0 && func_0011BBB8(a2) != 0) {
 *       v0 = func_0011BB48(a2);        ; jal delay: a0 = s0
 *       v1 = 0x8101005B;               ; lui 0x8101 / ori 0x5B
 *       if (v0 != 0) v1 = 0;           ; movn $v1,$zero,$v0
 *       return v1;
 *   }
 *   return 0x81010016;                 ; lui 0x8101 / ori 0x16
 *
 * func_0011BFB0 = the 3-argument record checker (asm/cod/01BFB0.s), 0011BBB8 =
 * the "'?'/'*'/control character" validator (src/non_matching/01BBB8.c), and
 * 0011BB48 = its companion. 0x81010016/0x8101005B are the two return codes.
 * The `if (v0 != 0) v1 = 0;` if-conversion into movn needs the constant in a
 * register first, which is the statement order below.
 * MATCH GUESS: cc=29 (16-byte-spaced $s0/$ra frame, 0x20) */
int func_0011BFB0(int a0, int a1, int a2);
int func_0011BBB8(unsigned char *s);
int func_0011BB48(int a0);

int func_0011D988(int a0, int a1, int a2) {
    int s0 = a2;

    if (func_0011BFB0(a0, a1, a2) != 0) {
        if (func_0011BBB8((unsigned char *)s0) != 0) {
            int v0 = func_0011BB48(s0);
            int v1 = 0x8101005B;

            if (v0 != 0)
                v1 = 0;
            return v1;
        }
    }
    return 0x81010016;
}
