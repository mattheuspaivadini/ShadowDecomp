/* asm/cod/015048.s -> func_00115048 @ 0x00115048 (0x68 bytes, 26 insns)
 *
 * Tear down all 16 records of the 0x334-byte-stride table D_0014B598:
 *
 *   D_001339E8 = 0;                          ; `sw $zero,%lo(...)($v0)`
 *   p = D_0014B598;
 *   for (i = 0; i < 0x10; i++) {
 *       if (p->f00 != 0) {                   ; beql: i++ is in its delay slot
 *           r = func_001151B8(i);            ; the matched 0151B8 (syscall free)
 *           if (r < 0) return r;             ; bltz -> epilogue, $v0 = r
 *       }
 *       p = (rec *)((char *)p + 0x334);      ; `addiu $s1,$s1,0x334`
 *   }
 *   return 1;                                ; `addiu $v0,$zero,0x1`
 *
 * `i++` appears twice (once per body path) because the increment is scheduled
 * into both delay slots. D_001339E8 is in .data -> declared as an array so the
 * access stays absolute (lui/%lo), not %gp_rel.
 * MATCH GUESS: cc=29
 */
struct S015048 {
    int  field0;        /* 0x00 */
    char rest[0x330];   /* to 0x334 */
};

extern struct S015048 D_0014B598[];   /* .bss 0x0014B598: 16 records */
extern int D_001339E8[];              /* .data 0x001339E8 (libpad2 block) */

int func_001151B8(int index);

int func_00115048(void) {
    int i;
    int r;

    D_001339E8[0] = 0;
    for (i = 0; i < 0x10; i++) {
        if (D_0014B598[i].field0 != 0) {
            r = func_001151B8(i);
            if (r < 0)
                return r;
        }
    }
    return 1;
}
