/* asm/cod/021058.s -> func_00121058 @ 0x00121058
 * func_00107010(D_00163CC0[0]); then `sync` + `ei`. */
extern int D_00163CC0[];
void func_00107010(int a0);

void func_00121058(void) {
    func_00107010(D_00163CC0[0]);
    __asm__ __volatile__("sync" ::: "memory");
    __asm__ __volatile__("ei");
}
