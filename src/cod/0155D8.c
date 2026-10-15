/* asm/cod/0155D8.s -> func_001283D0.
 * PART1 0155D8 dropped redundant pre-loop p->f00=0 (store-order), MATCH cc=29
 * MATCHED (Session 8). */
struct R0155D8 {
    char pad00[0x10];
    char *buf;          /* 0x10 */
    char  pad14[0x320]; /* to 0x334 */
};

struct B0155D8 {
    unsigned char f00;      /* 0x00 */
    unsigned char f01;      /* 0x01 */
    unsigned char f02;      /* 0x02 */
    unsigned char f03;      /* 0x03 */
    int           f04;      /* 0x04 */
    char          pad08[0x14];
    char          f1C[0x60];/* 0x1C */
    int           f7C;      /* 0x7C */
};

extern struct R0155D8 D_0014B598[];   /* .bss 0x0014B598: 16 records */

int func_001283D0(void *dst, int value, int size);

void func_001155D8(int index) {
    struct B0155D8 *p;
    int             i;

    p = (struct B0155D8 *)D_0014B598[index].buf;
    for (i = 1; i >= 0; i--) {
        p->f00 = 0;
        p->f7C = 0;
        p->f01 = 0;
        p->f03 = 0;
        p->f02 = 0;
        p->f04 = 0;
        func_001283D0(p->f1C, 0xFF, 0x20);
        p = (struct B0155D8 *)((char *)p + 0x80);
    }
}
