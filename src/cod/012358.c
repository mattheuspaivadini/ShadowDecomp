/* MATCHED (Session 5, step 1). Evidence: tools/permute.py ->
 * build/permute/012358/batch1.json (v06_order_00_04_0C_08, cc=29, score 0).
 *
 * asm/cod/012358.s -> func_00112358 @ 0x00112358 (0x28 bytes)
 *   lui   $v0, %hi(D_0014AEC0)
 *   addiu $v1, $v0, %lo(D_0014AEC0)
 *   sw    $a0, %lo(D_0014AEC0)($v0)
 *   addiu $a0, $v1, 0x10
 *   daddu $v0, $v1, $zero
 *   sw    $a0, 0x8($v1)
 *   sw    $zero, 0x4($v1)
 *   jr    $ra
 *    sw   $a0, 0xC($v1)
 *
 * A queue/list link: store the argument at offset 0, set 0x4 to 0, point
 * 0x8/0xC at (base + 0x10) and return the base address.
 *
 * Matching notes:
 * - the field00 store keeps the *symbolic* `sw $a0,%lo(D)($v0)` form (sharing
 *   the `lui`) only when field00's statement is first;
 * - the emitted store order is field00, field04, field0C, field08 — the source
 *   statement order that reproduces it is 00, 04, 0C, 08 (the other five
 *   permutations score 2-3 with cc=29);
 * - cc=29 only (best cc=296 score is 7).
 */
struct S0014AEC0 {
    void *field00;   /* 0x00 */
    int   field04;   /* 0x04 */
    void *field08;   /* 0x08 */
    void *field0C;   /* 0x0C */
};

extern struct S0014AEC0 D_0014AEC0;

struct S0014AEC0 *func_00112358(void *arg) {
    D_0014AEC0.field00 = arg;
    D_0014AEC0.field04 = 0;
    D_0014AEC0.field0C = (char *)&D_0014AEC0 + 0x10;
    D_0014AEC0.field08 = (char *)&D_0014AEC0 + 0x10;
    return &D_0014AEC0;
}
