/* asm/cod/015778.s -> func_00115778.
 * libpad new-frame check; frame counter compared/stored through the record array (Session 22)
 * MATCHED. */
struct S015778 {
    int f00;
    int f04;
    int frame;          /* 0x08 */
    int f0C;
    unsigned char *buf; /* 0x10 */
    char pad14[0x320];  /* to 0x334 */
};

extern struct S015778 D_0014B598[];
unsigned char *func_001156A8(int index);

int func_00115778(int index) {
    int v = *(int *)(func_001156A8(index) + 0x7C);
    if (v == 0 || v == D_0014B598[index].frame)
        return 0;
    D_0014B598[index].frame = v;
    return 1;
}
