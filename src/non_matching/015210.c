/* STATUS (Session 9, 2026-10-15): NON_MATCHING. best score 17 [cc=29].
 * session9 R2 waveA; residual class not auto-classified
 * The original .s stays in the build (asm/cod/015210.s); this C
 * draft (Session 9) is kept for the record. */
struct R015210 {
    int f00;                 /* 0x00 */
    unsigned char f02;       /* 0x02 */
    unsigned char f03;       /* 0x03 */
    int f04;                 /* 0x04 */
    char pad08[0x14];        /* 0x08 */
    unsigned char name[1];   /* 0x1C */
    char pad1D[0x317];       /* up to 0x334 */
};

extern struct R015210 D_0014B598[];   /* .bss 0x0014B598: 16 records */
extern char D_0014B5AC[];             /* the parallel 0x334-stride table */

int func_00115650(int index);
void *func_001156A8(int index);
int func_0012821C(int dst, char *src, int n);
int func_001157D8(char *dst, char *src);

int func_00115210(int index, int a1) {
    struct R015210 *s0;

    if (D_0014B598[index].f00 == 0)
        return -1;
    if (D_0014B598[index].f04 == 0) {
        if (func_00115650(index) < 0)
            return -1;
    }
    s0 = func_001156A8(index);
    if (s0->f02 != 0 && (char *)s0 + 0x1C != 0) {
        func_0012821C(a1, (char *)s0 + 0x1C, s0->f02);
        func_001157D8((char *)s0 + s0->f02 + 0x1C, D_0014B5AC + index * 0x334);
    }
    return s0->f04 ? s0->f02 : -1;
}
