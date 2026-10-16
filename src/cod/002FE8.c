/* asm/cod/002FE8.s -> func_00102FE8 @ 0x00102FE8 (0x20 bytes, 8 insns)
 *   addiu $sp, $sp, -0x10
 *   daddu $a1, $a0, $zero            ; a1 = the incoming string
 *   sd    $ra, 0x0($sp)
 *   lui   $a0, %hi(D_00139FF8)       ; a0 = "%s"
 *   addiu $a0, $a0, %lo(D_00139FF8)
 *   ld    $ra, 0x0($sp)
 *   j     func_001285C0              ; the variadic print routine
 *    addiu $sp, $sp, 0x10
 *
 * Print one string through the shared "%s" object in .sdata (D_00139FF8 sits in
 * the "\n" / " 0" / "%s" format pool). func_001285C0 is the print entry point:
 * it saves a1-a7/f12-f19 and calls func_00129930(FILE, fmt, va_list), so this
 * wrapper is `printf("%s", s)` with the format taken from the shared object.
 *
 * The frame kept around the tail `j` is the cc=296 sibling-call shape.
 * MATCH GUESS: cc=296 */
extern char D_00139FF8[];            /* .sdata 0x00139FF8, "%s" */
int func_001285C0(char *fmt, ...);

void LoaderSysPutString(char *a0) {
    func_001285C0(D_00139FF8, a0);
}
