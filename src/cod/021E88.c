/* asm/cod/021E88.s -> func_00121E88 @ 0x00121E88
 * Look the record up by index (stride 0x24, `mult $a0,$a0,$v1` = the 2.9
 * generation), fetch its field at +0x04 through func_001161A0 and return
 * whether that result differs from 3 (`xori` + `sltu`). */
struct R021E88 {
    char pad00[0x4];
    int  field04;   /* 0x04 */
};

extern struct R021E88 D_00163CC8[];

int func_001161A0(int x);

int func_00121E88(int index) {
    return func_001161A0(D_00163CC8[index].field04) != 3;
}
