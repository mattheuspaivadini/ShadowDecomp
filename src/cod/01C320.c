/* asm/cod/01C320.s -> func_0011C320 @ 0x0011C320 (0x90 bytes, 36 insns)
 * Close record `index` of the 0x898-byte table D_0015DF48: when the record is
 * in use (field800 > 0) and armed (field894 == 1), hand it to
 * func_00120748(index, base + 0x400 + index * 0x898, field800, 1); a zero
 * result returns 0, anything else (or an idle/unarmed record) clears
 * field894 and returns 1.
 * The stride multiply is the R5900 3-operand `mult $a3,$s0,$v0` with 0x898
 * materialised into $v0 first (cc=29 shape, cf. the matched 020F18/01C198),
 * and the `+0x400` argument is grouped as (base + 0x400) + index * stride
 * (`addiu $a1,0x400` then `addu $a1,$a3,$a1`); the record address is
 * materialised twice (two separate subscripts), so the multiply appears twice.
 * MATCH GUESS: cc=29 */
struct R01C320 {
    char pad00[0x800];
    int  field800;      /* 0x800 */
    char pad804[0x90];
    int  field894;      /* 0x894 */
};

extern struct R01C320 D_0015DF48[];   /* .bss 0x0015DF48, 0x898-byte records */

int _sceMcpWriteClust(int a0, int a1, int a2, int a3);

int func_0011C320(int index) {
    if (D_0015DF48[index].field800 > 0 && D_0015DF48[index].field894 == 1) {
        if (_sceMcpWriteClust(index, (int)D_0015DF48 + 0x400 + index * 0x898,
                          D_0015DF48[index].field800, 1) == 0)
            return 0;
    }
    D_0015DF48[index].field894 = 0;
    return 1;
}
