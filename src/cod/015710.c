/* asm/cod/015710.s -> func_00115710.
 * libpad double-buffer pick (0x100 sync variant of 0156A8) (Session 22)
 * MATCHED. */
struct S015710 {
    char pad00[0x10];
    unsigned char *buf; /* 0x10 */
    char pad14[0x320];  /* to 0x334 */
};

extern struct S015710 D_0014B598[];   /* .bss 0x0014B598: 16 records */

void SyncDCache(void *start, void *end);

unsigned char *func_00115710(int index) {
    unsigned char *p[2];
    unsigned char *b;

    b = D_0014B598[index].buf;
    p[0] = b;
    p[1] = b + 0x80;
    SyncDCache(b, b + 0x100);
    return p[*(int *)(p[0] + 0x7C) < *(int *)(p[1] + 0x7C)];
}
