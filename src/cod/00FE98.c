/* asm/cod/00FE98.s -> func_0010FE98 @ 0x0010FE98 (0x68 bytes, 26 insns)
 *
 * Read-modify-write of an 8-byte register pair through the two hand-written
 * syscall trampolines func_00107090 (0x4B, read) / func_00107080 (0x4A, write)
 * (asm/cod/007090.s, 007080.s):
 *
 *   func_00107090(buf);                     ; read  -> buf[0], buf[1]
 *   v = buf[0];
 *   buf[1] = (v & 0xFFFF1FFF) | 0x2000;     ; clear bits 13/14, set bit 13
 *                                           ; (`sw $v1,0x4($sp)` in the jal slot)
 *   func_00107080(&buf[1]);                 ; write buf[1]
 *   func_00107090(&buf[1]);                 ; read  buf[1]
 *   func_00107080(buf);                     ; write buf[0]
 *   return ((buf[1] >> 13) & 7) == 0;       ; srl + andi + sltiu
 *
 * The `srl` (not `sra`) fixes the shift as *unsigned*; the `sltiu $v0,$v0,1`
 * is the `== 0` test. Frame 0x30: only $s0 (= &buf[1]) + $ra are saved.
 * MATCH GUESS: cc=296
 */
void GetOsdConfigParam(int *p);
void SetOsdConfigParam(int *p);

int func_0010FE98(void) {
    unsigned int buf[2];
    unsigned int v;

    GetOsdConfigParam((int *)buf);
    v = buf[0];
    buf[1] = (v & 0xFFFF1FFF) | 0x2000;
    SetOsdConfigParam((int *)&buf[1]);
    GetOsdConfigParam((int *)&buf[1]);
    SetOsdConfigParam((int *)buf);
    return ((buf[1] >> 13) & 7) == 0;
}
