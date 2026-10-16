/* asm/cod/021058.s -> func_00121058 @ 0x00121058
 * func_00107010(D_00163CC0[0]); then `sync` + `ei`. */
extern int D_00163CC0[];
void iSignalSema(int a0);

void func_00121058(void) {
    iSignalSema(D_00163CC0[0]);
    __asm__ __volatile__("sync" ::: "memory");
    __asm__ __volatile__("ei");
}
