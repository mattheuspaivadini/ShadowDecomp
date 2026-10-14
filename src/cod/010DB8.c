/* asm/cod/010DB8.s -> func_00110DB8 @ 0x00110DB8
 * func_0010FB20(); then func_00110D48() *with no argument setup* (the asm has
 * a bare `jal` - the callee takes no arguments); if the first result is
 * non-zero, func_0010FB70(); the second result is returned. */
int func_0010FB20(void);
int func_00110D48(void);
int func_0010FB70(void);

int func_00110DB8(void) {
    int a = func_0010FB20();
    int b = func_00110D48();

    if (a != 0)
        func_0010FB70();
    return b;
}
