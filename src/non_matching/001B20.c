/* STATUS (Session 7, 2026-10-14): NON_MATCHING. best score 11 [cc=296, default].
 * pointer-list walk + per-element call.
 * The original .s stays in the build (asm/cod/001B20.s); this C
 * draft (subagent-produced, Session 7) is kept for the record. */
/* asm/cod/001B20.s -> func_00101B20 @ 0x00101B20 (0x68 bytes, 26 insns)
 *
 * Walk the zero-terminated pointer list a1 and return 1 as soon as
 * func_00128E6C(element, a0) returns 0; return 0 when the terminator (a null
 * element) is reached:
 *
 *   v = *a1; if (v == 0) return 0;
 *   p = a1;
 *   do {
 *       e = *p;                       ; re-read every iteration (`lw $a0,0($s0)`
 *                                     ; appears in the preheader AND in the
 *                                     ; loop-back delay slot)
 *       p++;
 *       r = func_00128E6C(e, a0);
 *       if (r == 0) return 1;         ; `b ...; addiu $v0,$zero,1`
 *       v = *p;                       ; loop test re-read from memory
 *   } while (v != 0);
 *   return 0;
 *
 * Two loads from the same address per iteration ($v0 for the test, $a0 for the
 * call) => the source reads the element twice (test + argument), so the
 * argument is not a register variable.
 * MATCH GUESS: cc=29
 */
int func_00128E6C(char *record, const char *module);

int func_00101B20(const char *a0, char **a1) {
    char **p;
    char *e;

    p = a1;
    while (*p != 0) {
        e = *p;
        p++;
        if (func_00128E6C(e, a0) == 0)
            return 1;
    }
    return 0;
}
