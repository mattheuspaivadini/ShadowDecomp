/* asm/cod/02E7E8.s -> func_00131048.
 * session9 R1 w25b wave
 * MATCHED (Session 8). */
extern int func_00131048(int a0, int a1, int a2);

struct S02E7E8 {
    char pad00[0x4C];
    int *f4C;                    /* 0x4C: the free-list table */
};

int *func_0012E7E8(struct S02E7E8 *p, int i) {
    int *tbl;
    int *e;
    int mask;

    tbl = p->f4C;
    if (tbl == 0) {
        tbl = (int *)func_00131048((int)p, 4, 0x10);
        p->f4C = tbl;
        if (tbl == 0)
            return 0;
    }
    e = (int *)tbl[i];
    if (e != 0) {
        tbl[i] = e[0];
    } else {
        mask = 1 << i;
        e = (int *)func_00131048((int)p, 1, mask * 4 + 0x14);
        if (e == 0)
            return 0;
        e[1] = i;
        e[2] = mask;
    }
    e[4] = 0;
    e[3] = 0;
    return e;
}
