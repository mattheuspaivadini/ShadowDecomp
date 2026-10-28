/* KERNEL.XFF @ 0x01F420 (180 B) - MakeStrHashValue
 * Evidence: two-pass hash over every other byte (`for i in 0..1`, `j += 2`),
 * hash = hash*0x4D + (c - 0x2D), returned as the int in $2.
 *   - the early-out block tests `str == 0` first, then
 *     `strcmp(D_kernel_rodata_2B28, str) == 0` (lui/addiu of .rodata+0x2B28,
 *     the empty-string constant); both return 0.
 *   - `lb $2,0($3)` proves a *signed* byte read; the `0x4D` multiplier is
 *     hoisted into $20 once (`li s4,0x4D`) and the product is materialised in the
 *     inner-loop condition block (after the strlen call), so the body is exactly
 *     lb / addiu -0x2D / addu.
 *   - `hash` must be **unsigned int**: with a signed accumulator, fold-const
 *     rewrites `hash*0x4D + (c - 0x2D)` into `(hash*0x4D + c) - 0x2D` and the
 *     addiu/addu pair comes out in the wrong order (that was the 2-word
 *     residue). This is the only lever that closes the function.
 * UNCONFIRMED: the exact KERNEL symbol behind D_kernel_rodata_2B28, and the
 * parameter name.
 */
extern char D_kernel_rodata_2B28[];
int strcmp(const char *a, const char *b);
unsigned int strlen(const char *s);

int MakeStrHashValue(const char *str) {
    unsigned int hash = 0;
    unsigned int j;
    int i;

    if (str == 0 || strcmp(D_kernel_rodata_2B28, str) == 0) {
        return 0;
    }
    for (i = 0; i < 2; i++)
        for (j = i; j < strlen(str); j += 2) {
            hash = hash * 0x4D + ((signed char)str[j] - 0x2D);
        }
    return hash;
}
