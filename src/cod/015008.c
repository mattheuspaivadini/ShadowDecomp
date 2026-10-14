/* MATCHED (Session 5, step 1). Evidence: tools/permute.py ->
 * build/permute/015008/batch3.json (four independent spellings score 0 with
 * cc=29; the int-address form below is the one committed).
 *
 * asm/cod/015008.s -> func_00115008 @ 0x00115008 (0x40 bytes)
 *   addiu $v1, $zero, 0x1
 *   lui   $v0, %hi(D_001339E8)
 *   lui   $a0, %hi(D_0014B598)
 *   sw    $v1, %lo(D_001339E8)($v0)      ; D_001339E8 = 1
 *   addiu $a0, $a0, %lo(D_0014B598)      ; p = D_0014B598
 *   addiu $v1, $a0, 0x3340               ; end = p + 16 * 0x334
 * .Lloop:
 *   sw    $zero, 0x0($a0)
 *   sw    $zero, 0x4($a0)
 *   sw    $zero, 0x8($a0)
 *   sw    $zero, 0xC($a0)
 *   addiu $a0, $a0, 0x334                ; next record
 *   slt   $v0, $a0, $v1                  ; SIGNED compare
 *   bnez  $v0, .Lloop
 *    nop
 *   jr    $ra
 *    addiu $v0, $zero, 0x1               ; return 1
 *
 * Matching notes:
 * - the declarations must carry NO initialisers: `D_001339E8 = 1;` is the
 *   first *assignment*, so `li $v1,1` and the store's `lui` are materialised
 *   before the loop pointers (score 7 otherwise);
 * - the loop registers are plain `int` addresses, which is what produces the
 *   signed `slt` (pointer locals give `sltu`, score 7-9);
 * - cc=29 only. D_001339E8 lives in .data and is addressed absolutely, so it
 *   is declared non-small. The 0x334 stride and 16-record extent are
 *   evidence-backed; record content UNCONFIRMED.
 */
#include "symbols.h"

extern __attribute__((section(".data"))) int D_001339E8;

struct S015008 {
    int field0;         /* 0x0 */
    int field4;         /* 0x4 */
    int field8;         /* 0x8 */
    int fieldC;         /* 0xC */
    char rest[0x324];   /* to 0x334 */
};

extern struct S015008 D_0014B598[];

int func_00115008(void) {
    int base;
    int p;
    int end;

    D_001339E8 = 1;
    base = (int)D_0014B598;
    p = base;
    end = base + 0x3340;
    do {
        *(int *)(p + 0x0) = 0;
        *(int *)(p + 0x4) = 0;
        *(int *)(p + 0x8) = 0;
        *(int *)(p + 0xC) = 0;
        p += 0x334;
    } while (p < end);
    return 1;
}
