/* v02: void-returning first callee (frees $v0 for the base register). */
void func_0010A740(void);
int func_00107020(int x);

extern int D_0013231C[];

int func_0010A798(void) {
    func_0010A740();
    func_00107020(D_0013231C[0]);
    return 0;
}
