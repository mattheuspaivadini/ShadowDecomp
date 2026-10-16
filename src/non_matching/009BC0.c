/* STATUS (10, 2026-10-16): NON_MATCHING. best score 5 [cc=29].
 * 
 * The original .s stays in the build (asm/cod/009BC0.s); this C
 * draft (10) is kept for the record. */
extern char D_00145940[];               /* lui/%lo - non-small */
int func_0010FB20(void);
int func_0010FB70(void);

void sceSifSetRpcQueue(int *a0, int a1) {
    int *p;
    int *head;

    func_0010FB20();
    a0[0] = a1;
    a0[1] = 0;
    a0[2] = 0;
    a0[3] = 0;
    a0[4] = 0;
    a0[5] = 0;
    head = *(int **)(D_00145940 + 0x28);
    if (head == 0) {
        *(int **)(D_00145940 + 0x28) = a0;
    } else {
        p = head;
        while (*(int **)((char *)p + 0x14) != 0)
            p = *(int **)((char *)p + 0x14);
        *(int **)((char *)p + 0x14) = a0;
    }
    func_0010FB70();
}
