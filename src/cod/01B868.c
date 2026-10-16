/* func_0011B868 @ 0x0011B868 (0x3C bytes): call func_0011AB28;
 * if it returns 0, fix the error up through func_0011B670(0, 0, &v).
 * Matching note: the early `return v` (not the merged `if (v == 0) ...;
 * return v;`) is what makes ee-gcc reload v into $v0 directly at the tail. */
int sceMc2WriteFileAsync(void);
int func_0011B670(int a, int b, int *out);

int sceMc2WriteFile(void) {
    int v = sceMc2WriteFileAsync();

    if (v != 0)
        return v;
    func_0011B670(0, 0, &v);
    return v;
}
