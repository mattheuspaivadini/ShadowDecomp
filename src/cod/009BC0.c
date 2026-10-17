/* asm/cod/009BC0.s -> sceSifSetRpcQueue.
 * SCE SDK, cc=29 (callee arity / tail-call / base pin from the image)
 * MATCHED. */
extern char D_00145940[];               /* lui/%lo - non-small */
int DIntr(void);
void EIntr(void);

void sceSifSetRpcQueue(int *a0, int a1) {
    int *p;
    int *head;
    char *q;

    DIntr();
    a0[0] = a1;
    a0[1] = 0;
    q = D_00145940;
    asm volatile ("" : "+r" (q));
    a0[2] = 0;
    a0[3] = 0;
    a0[4] = 0;
    a0[5] = 0;
    head = *(int **)(q + 0x28);
    if (head == 0) {
        *(int **)(q + 0x28) = a0;
    } else {
        p = head;
        while (*(int **)((char *)p + 0x14) != 0)
            p = *(int **)((char *)p + 0x14);
        *(int **)((char *)p + 0x14) = a0;
    }
    EIntr();
}
