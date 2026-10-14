/* asm/cod/021E88.s -> func_00121E88 @ 0x00121E88
 *
 * Look the record up by index (stride 0x24, `mult $a0,$a0,$v1` = the 2.9
 * generation), fetch its field at +0x04 through func_001161A0 and return
 * whether that result differs from 3 (`xori` + `sltu`).
 *
 * MATCHED (Session 6, step 3) with cc=29. The struct must model the 0x24
 * stride (`char rest[0x24 - 8]`); with `{ char pad00[4]; int field04; }`
 * alone the stride is 8 and the address math is a `sll` instead of the
 * original's `addiu 0x24` + `mult`.
 */
struct R021E88 {
    char pad00[0x4];
    int  field04;                /* 0x04 */
    char rest[0x24 - 8];         /* stride 0x24 */
};

extern struct R021E88 D_00163CC8[];

int func_001161A0(int x);

int func_00121E88(int index) {
    return func_001161A0(D_00163CC8[index].field04) != 3;
}
