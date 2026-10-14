/* asm/cod/007C48.s -> func_00107C48 @ 0x00107C48
 * func_00107010(a3); then `sync` + `ei`; returns 0. */
void func_00107010(int a0);

int func_00107C48(int a0, int a1, int a2, int a3) {
    func_00107010(a3);
    __asm__ __volatile__("sync" ::: "memory");
    __asm__ __volatile__("ei");
    return 0;
}
