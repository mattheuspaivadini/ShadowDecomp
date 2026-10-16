/* MATCHING (Session 4, 2026-10-14) with the ALTERNATE EE-GCC revision
 * (manifest token `cc=29` = ee-gcc2.9-991111-01). ee-gcc2.96 expands the
 * constant stride into a shift/add sequence; 2.9 emits the R5900 3-operand
 * `mult rd,rs,rt` even for a *literal* stride (probe: tools/cc/probe_mult.sh,
 * and a literal-vs-local probe in docs/compiler.md 4.2). See 4.3.
 *
 * asm/cod/020F18.s -> func_00120F18 @ 0x00120F18 (0x18 bytes)
 *   addiu $v1, $zero, 0x184
 *   lui   $v0, %hi(D_00135638)
 *   mult  $a0, $a0, $v1              ; i * 0x184  (R5900 3-operand MULT)
 *   addiu $v0, $v0, %lo(D_00135638)
 *   jr    $ra
 *    addu $v0, $a0, $v0              ; &D_00135638[i]
 *
 * The 0x184 element stride is evidence-backed; the element content UNCONFIRMED.
 */
struct S020F18 {
    char bytes[0x184];
};

extern struct S020F18 gSceMc2SysInfo[];

struct S020F18 *_SceMcComGetSysInfo(int i) {
    return (struct S020F18 *)((char *)gSceMc2SysInfo + i * 0x184);
}
