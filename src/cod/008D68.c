/* func_00108D68 @ 0x00108D68 (0x28 bytes): guard + call(func_00107CA8), return 1.
 * Third argument is forwarded; the copy `a0 = arg` is what the
 * `beqz` tests. */
int func_00107CA8(int x);

int func_00108D68(int a, int b, int c) {
    a = c;
    if (a != 0)
        func_00107CA8(a);
    return 1;
}
