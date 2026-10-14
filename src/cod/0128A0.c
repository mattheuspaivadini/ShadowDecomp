/* asm/cod/0128A0.s -> func_001128A0 @ 0x001128A0 (0x20 bytes)
 *   lw    $v0, 0x10($a0)     ; a[4]
 *   lw    $a2, 0x1C($a1)     ; b->field1C
 *   lw    $v1, 0x14($a0)     ; a[5]
 *   sll   $v0, $v0, 2
 *   addu  $v0, $v0, $a2
 *   jr    $ra
 *    sw   $v1, 0x0($v0)
 */
struct S00128A0 {
    char pad00[0x1C];
    int *field1C;   /* 0x1C */
};

void func_001128A0(int *a, struct S00128A0 *b) {
    b->field1C[a[4]] = a[5];
}
