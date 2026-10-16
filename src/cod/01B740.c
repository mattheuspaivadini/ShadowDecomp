/* asm/cod/01B740.s -> func_0011B740 @ 0x0011B740 (0x24 bytes, 9 insns)
 *
 * Wrapper: forwards (0, a0, a1) to func_0011B670 and returns its result.
 * Same argument shift as func_0011B718 but the first argument is 0
 * (`daddu a0, $zero, $zero` in the jal delay slot).
 *
 * MATCHED (Session 6, step 1) with cc=29 (2.9-ee-991111-01), via the
 * intermediate-result shape (`int r = ...; return r;`); the plain
 * `return f(0, a, b);` is one instruction off.
 */
int func_0011B670(int a0, int a1, int a2);

int sceMc2Sync(int a0, int a1) {
    int r = func_0011B670(0, a0, a1);

    return r;
}
