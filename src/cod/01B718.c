/* asm/cod/01B718.s -> func_0011B718 @ 0x0011B718 (0x24 bytes, 9 insns)
 *
 * Wrapper: forwards (1, a0, a1) to func_0011B670 and returns its result.
 * The original shifts the arguments right without a staging register
 * (`a2=a1; a1=a0` then `a0=1` in the jal delay slot).
 *
 * MATCHED (Session 6, step 1) with cc=29 (2.9-ee-991111-01): the 2.9
 * generation does not perform sibling-call optimization, so the plain
 * `return func_0011B670(1, a0, a1);` keeps the `jal` + epilogue shape; the
 * 2.96 generation tail-calls (`j`) and cannot match without
 * `-fno-optimize-sibling-calls` (and the 2.9 cc1 rejects that flag).
 */
int func_0011B670(int a0, int a1, int a2);

int sceMc2CheckAsync(int a0, int a1) {
    return func_0011B670(1, a0, a1);
}
