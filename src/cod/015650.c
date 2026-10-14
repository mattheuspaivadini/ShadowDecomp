/* asm/cod/015650.s -> func_00115650 @ 0x00115650 (0x54 bytes, 21 insns)
 *
 * Sibling of func_001151B8 on the same D_0014B598 records, but the value comes
 * from sceDbcGetDepNumber(index):
 *
 *   r = sceDbcGetDepNumber(index);  ; daddu $a3,$v0,$zero
 *   bltz $a3 -> epilogue            ; failure: $v0 still holds r
 *   mult  $a0,$s0,0x334             ; index * 0x334 (R5900 3-operand mult)
 *   rec->fieldC = r                 ; sw    $a3,0xC($rec)
 *   rec->field4 = 1                 ; sw    $a2,0x4($rec)  ($a2 = 1)
 *   return r                        ; daddu $v0,$a3,$zero
 *
 * Store order follows the asm (0x0C first, then 0x04).
 * MATCH GUESS: cc=29
 */
struct S015650 {
    int field0;         /* 0x0 */
    int field4;         /* 0x4 */
    int field8;         /* 0x8 */
    int fieldC;         /* 0xC */
    char rest[0x324];   /* to 0x334 */
};

extern struct S015650 D_0014B598[];   /* .bss 0x0014B598: 16 records */

int sceDbcGetDepNumber(int id);

int func_00115650(int index) {
    int r;

    r = sceDbcGetDepNumber(index);
    if (r < 0)
        return r;
    D_0014B598[index].fieldC = r;
    D_0014B598[index].field4 = 1;
    return r;
}
