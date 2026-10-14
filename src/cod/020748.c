/* asm/cod/020748.s -> func_00120748 @ 0x00120748
 * Look up the record at `index` (stride 0x184), read the unsigned short at
 * +0x2A and forward func_00121A90(index, a1, a2 * w, a3 * w). The two scaled
 * arguments are computed with the R5900 `mult $zero,rs,rt` + `mflo` shape. */
struct R020748 {
    char pad00[0x2A];
    unsigned short w;   /* 0x2A */
};

extern struct R020748 D_00135638[];

int func_00121A90(int a0, int a1, int a2, int a3);

int func_00120748(int index, int a1, int a2, int a3) {
    unsigned short w = D_00135638[index].w;

    return func_00121A90(index, a1, a2 * w, a3 * w);
}
