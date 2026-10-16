/* asm/cod/027448.s -> func_00127448.
 * abort (matched after T004 split of 027460)
 * MATCHED (Session 12). */
int raise(int sig);
void func_001000C0(int status) __attribute__((noreturn));

void func_00127448(void) {
    raise(6);
    func_001000C0(1);
}
