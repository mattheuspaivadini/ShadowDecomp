/* asm/cod/015888.s -> func_00115888 @ 0x00115888 (0x34 bytes, 13 insns)
 *
 * String/entry lookup by index - D_001339F8 is the 4-element pointer table
 * {D_001385B0 "NOLINK", D_001385A8, D_001385A0, D_00138598} and D_001385B8 is
 * the 8 zero bytes right after it:
 *
 *   sltiu $v0, $a0, 0x4               ; unsigned index < 4
 *   beqz  $v0, .L001158B0
 *    lui  $v0, %hi(D_001385B8)        ; (else path's base, filled delay slot)
 *   lui   $v0, %hi(D_001339F8)
 *   sll   $v1, $a0, 2                 ; &D_001339F8[index]
 *   addiu $v0, $v0, %lo(D_001339F8)
 *   daddu $a0, $a1, $zero             ; arg0 = the caller's buffer
 *   addu  $v1, $v1, $v0
 *   j     func_00128FB0               ; copy table[index] into the buffer
 *    lw   $a1, 0x0($v1)               ; arg1 = table[index]
 * .L001158B0:
 *   lbu   $v1, %lo(D_001385B8)($v0)   ; out of range -> single 0 byte
 *   jr    $ra
 *    sb   $v1, 0x0($a1)
 *
 * `sltiu` (not `slti`) fixes the unsigned index. Both objects need absolute
 * addressing: D_001339F8 is a 16-byte table (declared without a size) and
 * D_001385B8 must stay an unknown-size `char[]` (8 bytes would be small data).
 * The bare `j` with no frame is the cc=29 void-tail-call shape (matched
 * 010400.c); func_00128FB0 itself is the copy helper called the same way by
 * asm/cod/0050B8.s (`func_00128FB0(dst, src)`, 0x40 bytes there).
 * MATCH GUESS: cc=29 (-g0: the `lui` of the else path is in the beqz delay slot)
 */
extern void *D_001339F8[];   /* .data 0x001339F8: 4 pointers */
extern char  D_001385B8[];   /* .rodata 0x001385B8: unknown size => absolute */

void func_00128FB0(void *dst, void *src);

void scePad2StateIntToStr(unsigned int index, void *dst) {
    if (index < 4) {
        func_00128FB0(dst, D_001339F8[index]);
        return;
    }
    *(unsigned char *)dst = D_001385B8[0];
}
