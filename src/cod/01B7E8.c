/* func_0011B7E8 @ 0x0011B7E8 (0x3C bytes): call func_0011A6E8;
 * if it returns 0, fix the error up through func_0011B670(0, 0, &v).
 * Matching note: the early `return v` (not the merged `if (v == 0) ...;
 * return v;`) is what makes ee-gcc reload v into $v0 directly at the tail. */
int sceMc2UnformatAsync(void);
int func_0011B670(int a, int b, int *out);

int sceMc2Unformat(void) {
    int v = sceMc2UnformatAsync();

    if (v != 0)
        return v;
    func_0011B670(0, 0, &v);
    return v;
}
