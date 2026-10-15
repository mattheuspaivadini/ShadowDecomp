/* STATUS (Session 9, 2026-10-15): NON_MATCHING. best score 64 [cc=29].
 * session9 R2 waveA; residual class not auto-classified
 * The original .s stays in the build (asm/cod/0153B8.s); this C
 * draft (Session 9) is kept for the record. */
struct S0153B8 {
    int f00;    /* 0x00 */
    int f04;    /* 0x04 in-use / receive state */
};

extern struct S0153B8 D_0014B598[];   /* .bss 0x0014B598: 0x334-byte records */

int func_00115650(int index);
int func_00115778(int index);
int func_00115710(int index);
void func_001155D8(int index);
int sceDbcReceiveData(int index, int tag, int *size, unsigned char *data);

int func_001153B8(int index) {
    struct S0153B8 *rec;
    int *p;
    long long tag;
    unsigned char b;
    int w;
    int r;

    rec = &D_0014B598[index];
    if (rec->f04 == 0) {
        if (func_00115650(index) < 0)
            return 0;
    }
    if (func_00115778(index) == 0) {
        tag = (tag & ~0x3FFFLL) | 0xC;
        tag = (tag & ~0xC000LL) | 0x8000;
        tag = (tag & ~0xFF0000) | 0x10000;
        tag = (tag & ~0xFF0000LL) | 0x1000000;
        r = sceDbcReceiveData(index, tag, &w, &b);
        if (r >= 0)
            return b;
        D_0014B598[index].f04 = 0;
        func_001155D8(index);
        return 0;
    }
    p = (int *)func_00115710(index);
    if (p[1] != 0) {
        b = *(unsigned char *)p;
    } else {
        if (func_00115650(index) < 0) {
            D_0014B598[index].f04 = 0;
            func_001155D8(index);
            return 0;
        }
        b = *(unsigned char *)p;
    }
    return b;
}
