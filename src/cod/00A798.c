/* v02: void-returning first callee (frees $v0 for the base register). */
void func_0010A740(void);
int WaitSema(int x);

extern int D_0013231C[];

int func_0010A798(void) {
    func_0010A740();
    WaitSema(D_0013231C[0]);
    return 0;
}
