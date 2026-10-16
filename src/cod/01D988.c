/* asm/cod/01D988.s -> func_0011D988.
 * func_0011D988 (ternary validation)
 * MATCHED (Session 12). */
int func_0011BFB0(int a0, int a1, int a2);
int func_0011BBB8(int a0);
int func_0011BB48(int a0);

int func_0011D988(int a0, int a1, int a2) {
    if (!func_0011BFB0(a0, a1, a2) || !func_0011BBB8(a2))
        return 0x81010016;
    return func_0011BB48(a2) ? 0 : 0x8101005B;
}
