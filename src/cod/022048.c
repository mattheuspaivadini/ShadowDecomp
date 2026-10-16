/* asm/cod/022048.s -> func_00122048 @ 0x00122048 (0x68 bytes, 26 insns)
 *
 * Delete record `index` of the 0x24-byte table D_00163CC8 (the matched
 * 022018/0211B8 family; func_00122018 is the "is it in use" test):
 *
 *   if (func_00122018(index) == 0)        ; bnez -> body; v0 = 0 otherwise
 *       return 0;
 *   rec = &D_00163CC8[index];             ; mult index,0x24 (R5900 3-operand)
 *   sceDbcDeleteSocket(rec->field4);      ; jal with `lw $a0,0x4($v0)` in shadow
 *   rec->field0 = 0;                      ; rec re-materialised: `addu $s1,$s1,$s0`
 *   return 1;
 *
 * The record address is built twice (once per subscript expression). Frame
 * 0x40: $s0 at 0x00 (saved in the first jal's shadow), $s1 at 0x10,
 * $s2 (index) at 0x20, $ra at 0x30.
 * MATCH GUESS: cc=29
 */
struct R022048 {
    int  field0;        /* 0x00 */
    int  field4;        /* 0x04 */
    char rest[0x1C];    /* to 0x24 */
};

extern struct R022048 D_00163CC8[];   /* .bss 0x00163CC8 */

int  _sceMcCoreCheckSocket(unsigned int i);
int  sceDbcDeleteSocket(int id);

int _sceMcCoreDeleteSocket(int index) {
    if (_sceMcCoreCheckSocket(index) == 0)
        return 0;
    sceDbcDeleteSocket(D_00163CC8[index].field4);
    D_00163CC8[index].field0 = 0;
    return 1;
}
