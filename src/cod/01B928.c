/* func_0011B928 @ 0x0011B928 (0x3C bytes): call func_0011B250;
 * if it returns 0, fix the error up through func_0011B670(0, 0, &v).
 * Matching note: the early `return v` (not the merged `if (v == 0) ...;
 * return v;`) is what makes ee-gcc reload v into $v0 directly at the tail. */
int sceMc2RenameAsync(void);
int func_0011B670(int a, int b, int *out);

int sceMc2Rename(void) {
    int v = sceMc2RenameAsync();

    if (v != 0)
        return v;
    func_0011B670(0, 0, &v);
    return v;
}
