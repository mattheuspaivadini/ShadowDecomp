/* asm/cod/0114D8.s -> func_0010FB20.
 * R4 w25a_1 (4-arg guard wrapper, a1 = long long)
 * MATCHED (Session 8). */
int func_0010FB20(void);
int func_0010FB70(void);
int func_001113E0(int a0, long long a1, int a2, int a3);

int func_001114D8(int a0, long long a1, int a2, int a3) {
    int g;
    int b;

    g = func_0010FB20();
    b = func_001113E0(a0, a1, a2, a3);
    if (g != 0)
        func_0010FB70();
    return b;
}
