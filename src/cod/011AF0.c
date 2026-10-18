/* asm/cod/011AF0.s -> memset.
 * sceSifInitRebootNotify: two counters + memset (Session 23)
 * MATCHED. */
void func_001283D0(void *dst, int val, int size);

extern int D_00133938[];
extern int D_0013393C[];
extern char D_0014AC88[];

/* func_001283D0 = memset (see config/symbol_addrs.txt). */
void sceSifInitRebootNotify(void) {
    D_00133938[0] = 0;
    D_0013393C[0] = 0;
    func_001283D0(D_0014AC88, 0, 0x200);
}
