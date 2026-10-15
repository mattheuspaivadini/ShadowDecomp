/* asm/cod/006390.s -> func_00106390.
 * R4 w25a_0 (nested-loop biv)
 * MATCHED (Session 8). */
struct E006390 {
    int           field00;   /* 0x00 */
    unsigned char field04;   /* 0x04 */
    char          pad05[3];  /* to 0x08 */
};

extern struct E006390 D_0013A160;    /* .sdata, gp-relative template record */
extern struct E006390 D_0013ED90[];  /* .bss: 40 rows x 60 records */

void func_00106390(void) {
    int i;
    int j;

    for (i = 1; i < 0x28; i++)
        for (j = 0; j < 0x3C; j++)
            D_0013ED90[(i - 1) * 0x3C + j] = D_0013ED90[i * 0x3C + j];
    for (j = 0; j < 0x3C; j++)
        D_0013ED90[0x27 * 0x3C + j] = D_0013A160;
}
