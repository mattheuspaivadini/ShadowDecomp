/* asm/cod/023260.s -> func_00123260 @ 0x00123260 (0x90 bytes, 36 insns)
 * Issue a DBC command over the shared buffer:
 *   h = func_001231A8();                    (one-shot CreateSema for
 *                                            D_00135960; negative on failure)
 *   if (h < 0) { func_00108EF8(D_00138E08, a2); return h; }
 *   return SceSifrpcCall(a0, a2, 1, a1, 0x1000, a1, 0x1000,
 *                        (int)func_00123180, h);   (9-arg RPC-style call: the
 *                        9th argument is the `sw $s0,0x0($sp)` stack word)
 * The command descriptor is the a1 argument (passed as both the 4th and 6th
 * argument) and a2 rides along as the 2nd argument and the error-report
 * argument. Frame 0x60: $s0-$s3 + $ra at 0x10..0x50 plus the stack argument.
 * MATCH GUESS: cc=29 (0231A8/023208 D_00135960 family; filled jal shadows) */
int func_001231A8(void);
int func_00108EF8(const char *msg, int a1);
int SceSifrpcCall(int a0, int a1, int a2, int a3, int a4, int a5, int a6,
                  int a7, int a8);
void func_00123180(int a0);

extern char D_00138E08[];

int func_00123260(int a0, int a1, int a2) {
    int h;

    h = func_001231A8();
    if (h < 0) {
        func_00108EF8(D_00138E08, a2);
        return h;
    }
    return SceSifrpcCall(a0, a2, 1, a1, 0x1000, a1, 0x1000, (int)func_00123180,
                         h);
}
