/* asm/cod/0156A8.s -> func_001156A8.
 * libpad double-buffer pick; two-frame pointer array indexed by the frame-counter compare (Session 22)
 * MATCHED. */
struct S0156A8 {
    char pad00[0x10];
    unsigned char *buf; /* 0x10 */
    char pad14[0x320];  /* to 0x334 */
};

extern struct S0156A8 D_0014B598[];   /* .bss 0x0014B598: 16 records */

void SyncDCache(void *start, void *end);

unsigned char *func_001156A8(int index) {
    unsigned char *p[2];
    unsigned char *b;

    b = D_0014B598[index].buf;
    p[0] = b;
    p[1] = b + 0x80;
    SyncDCache(b, b + 0xFF);
    return p[*(int *)(p[0] + 0x7C) < *(int *)(p[1] + 0x7C)];
}
