/* func_0011BA68 @ 0x0011BA68 (0x3C bytes): call func_0011A858;
 * if it returns 0, fix the error up through func_0011B670(0, 0, &v).
 * Matching note: the early `return v` (not the merged `if (v == 0) ...;
 * return v;`) is what makes ee-gcc reload v into $v0 directly at the tail. */
int sceMc2SearchFileAsync(void);
int func_0011B670(int a, int b, int *out);

int sceMc2SearchFile(void) {
    int v = sceMc2SearchFileAsync();

    if (v != 0)
        return v;
    func_0011B670(0, 0, &v);
    return v;
}
