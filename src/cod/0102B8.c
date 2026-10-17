/* asm/cod/0102B8.s -> InitAlarm.
 * SCE SDK, cc=29 (callee arity / tail-call / base pin from the image)
 * MATCHED. */
void func_00110250(int a0, int a1);
int func_00110260(int a0, void *a1, int a2);
int FlushCache(int a0);
int func_001102A8(int a0);

extern int D_001338D8[];   /* lui/%lo -> non-small */
extern int D_00133170[];   /* lui/addiu -> non-small */
extern int D_001338B0[];   /* lui/addiu -> non-small */

void InitAlarm(void) {
    unsigned int i;
    int *q;

    if (*(volatile unsigned int *)0x10001810 & 0x100)
        return;
    func_00110250(D_001338D8[0], D_001338D8[1]);
    func_00110260(0x80076000, D_00133170, 0x740);
    func_00110260(0x82000, D_001338B0, 0x28);
    FlushCache(0);
    FlushCache(2);
    func_00110250(D_001338D8[2], D_001338D8[3]);
    q = &D_001338D8[4];
    for (i = 2; i < 8; i++) {
        func_00110250(*q, func_001102A8(*q));
        q += 2;
    }
}
