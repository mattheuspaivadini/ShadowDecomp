/* asm/cod/008E08.s -> func_00107FF8.
 * byte-exact under EE-GCC 2.95.3-136 (PE/wine); residue sweep found the third generation
 * MATCHED (Session 8). */
/* func_00108E08 @ 0x00108E08 (0x38 bytes): stack buffer + callback
 * func_00108D10 forwarded to func_00107FF8. */
int func_00107FF8(int (*cb)(void), int *p, int a1, int a2, int a3);
int func_00108D10(void);

void func_00108E08(int a0, int a1, int a2, int a3) {
    int buf;

    buf = a0;
    func_00107FF8(func_00108D10, &buf, a1, a2, a3);
}
