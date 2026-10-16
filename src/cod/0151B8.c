/* asm/cod/0151B8.s -> func_001151B8 @ 0x001151B8 (0x54 bytes, 21 insns)
 *
 * Tear down record `index` of the 0x334-byte-stride table D_0014B598:
 *
 *   r = sceDbcDeleteSocket(index)
 *   bltz $v0 -> epilogue          ; failure: $v0 already holds r, so `return r`
 *                                 ; needs no copy at all
 *   mult  $a0,$s0,0x334           ; index * 0x334 (R5900 3-operand mult)
 *   sw    $zero,0x0($rec)         ; 0x00
 *   sw    $zero,0x4($rec)         ; 0x04
 *   sw    $zero,0xC($rec)         ; 0x0C
 *   return 1                      ; addiu $v0,$zero,0x1
 *
 * The record address is materialised twice ($a1 = off+base, $a2 = base+off),
 * i.e. the three cleared fields are three separate `D_0014B598[index]`
 * subscript expressions.
 * MATCH GUESS: cc=29 (3-operand `mult` constant stride; same table/structure as
 * the matched 015008.c and 0211B8.c)
 */
struct S0151B8 {
    int field0;         /* 0x0 */
    int field4;         /* 0x4 */
    int field8;         /* 0x8 */
    int fieldC;         /* 0xC */
    char rest[0x324];   /* to 0x334 */
};

extern struct S0151B8 D_0014B598[];   /* .bss 0x0014B598: 16 records */

int sceDbcDeleteSocket(int id);

int scePad2DeleteSocket(int index) {
    int r;

    r = sceDbcDeleteSocket(index);
    if (r < 0)
        return r;
    D_0014B598[index].field0 = 0;
    D_0014B598[index].field4 = 0;
    D_0014B598[index].fieldC = 0;
    return 1;
}
