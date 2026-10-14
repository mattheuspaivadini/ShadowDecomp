/* asm/cod/020708.s -> func_00120708 @ 0x00120708
 * Look up the record at `index` (stride 0x184), read the unsigned short at
 * +0x2A and forward func_00121A70(index, a1, a2 * w, a3 * w). The two scaled
 * arguments are computed with the R5900 `mult $zero,rs,rt` + `mflo` shape. */
struct R020708 {
    char pad00[0x2A];
    unsigned short w;   /* 0x2A */
};

extern struct R020708 D_00135638[];

int func_00121A70(int a0, int a1, int a2, int a3);

int func_00120708(int index, int a1, int a2, int a3) {
    unsigned short w = D_00135638[index].w;

    return func_00121A70(index, a1, a2 * w, a3 * w);
}
